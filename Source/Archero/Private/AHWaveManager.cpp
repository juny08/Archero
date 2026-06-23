#include "AHWaveManager.h"
#include "AHGameState.h"
#include "Kismet/GameplayStatics.h"

AAHWaveManager::AAHWaveManager()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentWaveIndex = 0;
	AliveEnemies = 0;
}

void AAHWaveManager::BeginPlay()
{
	Super::BeginPlay();

	GS = GetWorld()->GetGameState<AAHGameState>();
	StartWave();
}

void AAHWaveManager::StartWave()
{
	if (!Waves.IsValidIndex(CurrentWaveIndex)) return;

	const FWaveData& Wave = Waves[CurrentWaveIndex];

	SpawnedCount = 0;
	AliveEnemies = 0;

	if (GS)
	{
		GS->CurrentWave = CurrentWaveIndex + 1;
		GS->SetRemainingMonsters(Wave.Count);
	}

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AAHWaveManager::SpawnEnemy,
		Wave.SpawnInterval,
		true
	);
}

void AAHWaveManager::SpawnEnemy()
{
	const FWaveData& Wave = Waves[CurrentWaveIndex];

	if (SpawnedCount >= Wave.Count)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	if (SpawnPoints.Num() == 0) return;

	int Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
	FVector SpawnLoc = SpawnPoints[Index]->GetSpawnLocation();

	GetWorld()->SpawnActor<AAHEnemyCharacter>(Wave.EnemyClass, SpawnLoc, FRotator::ZeroRotator);

	SpawnedCount++;
	AliveEnemies++;
}

void AAHWaveManager::OnEnemyKilled()
{
	AliveEnemies--;

	if (GS)
	{
		GS->RemoveRemainingMonster();
	}

	if (AliveEnemies <= 0)
	{
		CurrentWaveIndex++;
		StartWave();
	}
}
