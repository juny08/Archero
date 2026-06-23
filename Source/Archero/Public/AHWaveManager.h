// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHEnemySpawnPoint.h"
#include "AHEnemyCharacter.h"
#include "AHWaveManager.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAHEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere)
	int Count = 5;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 0.f;
};

UCLASS()
class ARCHERO_API AAHWaveManager : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Wave")
	TArray<FWaveData> Waves;

	UPROPERTY(EditAnywhere, Category = "Wave")
	TArray<AAHEnemySpawnPoint*> SpawnPoints;

private:
	class AAHGameState* GS;

public:
	AAHWaveManager();
	void OnEnemyKilled();

private:
	int CurrentWaveIndex;
	int AliveEnemies;

	FTimerHandle SpawnTimerHandle;
	int SpawnedCount;

	void StartWave();
	void SpawnEnemy();


};
