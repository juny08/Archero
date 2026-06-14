// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AHGameState.generated.h"

UCLASS()
class ARCHERO_API AAHGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	class AAHPlayerCharacter* player = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UAHPlayWidget> PlayWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "GameRules")
	int currentStage = 1;

	UPROPERTY(VisibleAnywhere, Category = "GameRules")
	int remainingMonsters = 0;

	UPROPERTY(VisibleAnywhere, Category = "GameRules")
	int currentWave = 1;

	UPROPERTY(EditAnywhere, Category = "GameRules")
	int maxWaves = 3;
	
public:
	AAHGameState();

	virtual void BeginPlay() override;

	// 스테이지 제어 함수들
	void NextStage();
	int GetCurrentStage() const { return currentStage; }

	// 몬스터 마리수 관리
	void MonsterSpawned();
	void MonsterKilled();
	int GetRemainingMonsters() const { return remainingMonsters; }

protected:
	void StartNextWave();
	void MoveToNextLevel();

};
