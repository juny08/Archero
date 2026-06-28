// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHWaveManager.generated.h"

class AAHEnemySpawnPoint;

UCLASS()
class ARCHERO_API AAHWaveManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Wave")
	TArray<AAHEnemySpawnPoint*> SpawnPoints;

	//UPROPERTY(EditAnywhere)
	//TArray<FName> StageLevels;

	UPROPERTY()
	class AAHGameState* GS;

	int MaxWave = 0;
	int CurrentWaveIndex;
	int AliveEnemies;

public:
	AAHWaveManager();

public:
	void OnEnemyKilled();
	void StartWave();
	void SpawnEnemies();
	void NextLevel();

public:
	virtual void BeginPlay() override;
};
