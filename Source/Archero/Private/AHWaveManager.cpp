#include "AHWaveManager.h"
#include "AHGameState.h"
#include "AHEnemySpawnPoint.h"
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

	// MaxWave 찾기
	for (AAHEnemySpawnPoint* Point : SpawnPoints)
	{
		if (Point)
		{
			MaxWave = FMath::Max(MaxWave, Point->SpawnWave);
		}
	}

	// 스폰설정
	SpawnPoints.Empty();

	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(), 
		AAHEnemySpawnPoint::StaticClass(), 
		FoundActors
	);
	
	for (AActor* Actor : FoundActors)
	{ 
		AAHEnemySpawnPoint* Point = Cast<AAHEnemySpawnPoint>(Actor);

		if (Point)
			SpawnPoints.Add(Point);
	}

	GS = GetWorld()->GetGameState<AAHGameState>();
	
	StartWave();
}

void AAHWaveManager::StartWave()
{
	AliveEnemies = 0;

	

	if (GS)
	{
		GS->CurrentWave = CurrentWaveIndex + 1;
	}

	SpawnEnemies();
}

void AAHWaveManager::SpawnEnemies()
{
	int CurrentWave = CurrentWaveIndex + 1;

	for (AAHEnemySpawnPoint* Point : SpawnPoints)
	{
		if (!Point) continue;

		// 현재 웨이브에 해당하는 스폰포인트만
		if (Point->SpawnWave != CurrentWave) continue;
		if (!Point->EnemyClass) continue;

		GetWorld()->SpawnActor<AAHEnemyCharacter>(
			Point->EnemyClass,
			Point->GetSpawnLocation(),
			FRotator::ZeroRotator
		);

		AliveEnemies++;
	}

	if (GS)
	{
		GS->SetRemainingMonsters(AliveEnemies);
	}

}

void AAHWaveManager::NextLevel()
{
	GS->CurrentStage++; // GameInstance로 옮길거임
	GS->CurrentWave = 1;
	FString LevelName = FString::Printf(TEXT("Stage%d"), GS->CurrentStage);
	UGameplayStatics::OpenLevel(this, FName(*LevelName));
	//UGameplayStatics::OpenLevel(this, StageLevels[GS->CurrentStage]);
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

		if (CurrentWaveIndex >= MaxWave)
		{
			NextLevel();
			return;
		}

		StartWave();
	}
}
