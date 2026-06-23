// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHWaveManager.generated.h"

UCLASS()
class ARCHERO_API AAHWaveManager : public AActor
{
	GENERATED_BODY()

public:
	void StartWave(int WaveIndex);
	void SpawnEnemy();
	void OnEnemyKilled();

private:
	int AliveEnemies;

public:	
	AAHWaveManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
