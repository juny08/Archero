#include "AHWaveManager.h"

void AAHWaveManager::StartWave(int WaveIndex)
{
	// SpawnPoint 선택
	// Enemy 생성
	// AliveEnemies++
}

void AAHWaveManager::SpawnEnemy()
{

}

void AAHWaveManager::OnEnemyKilled()
{
	AliveEnemies--;

	if (AliveEnemies <= 0)
	{
		//StartNextWave(...);
	}
}

// Sets default values
AAHWaveManager::AAHWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAHWaveManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAHWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

