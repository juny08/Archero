// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AHGameState.generated.h"

UCLASS()
class ARCHERO_API AAHGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AAHGameState();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameRules")
	int CurrentStage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameRules")
	int CurrentWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameRules")
	int RemainingMonsters;

	// 상태 변경용 함수 (외부에서 호출)
	void SetRemainingMonsters(int Count) { RemainingMonsters = Count; }
	void AddRemainingMonster() { RemainingMonsters++; }
	void RemoveRemainingMonster() { RemainingMonsters--; }
};