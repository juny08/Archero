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
	UPROPERTY()
	class AAHPlayerCharacter* Player = nullptr;

	// UI Class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UAHPlayWidget> PlayWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> LevelUpWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UAHJoyStickWidget> JoystickWidgetClass;

	// UI Instance
	UPROPERTY()
	class UAHPlayWidget* PlayWidgetInstance = nullptr;

	UPROPERTY()
	class UAHJoyStickWidget* JoystickWidgetInstance = nullptr;

	UPROPERTY()
	class UUserWidget* LevelUpWidgetInstance = nullptr;

	// Rules
	UPROPERTY(VisibleAnywhere, Category = "GameRules")
	int CurrentStage = 1;

	UPROPERTY(VisibleAnywhere, Category = "GameRules")
	int RemainingMonsters = 0;

	UPROPERTY(VisibleAnywhere, Category = "GameRules")
	int CurrentWave = 1;

	UPROPERTY(EditAnywhere, Category = "GameRules")
	int MaxWaves = 3;
	
public:
	AAHGameState();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	UAHJoyStickWidget* GetJoystickWidget() const { return JoystickWidgetInstance; }

	// 게임 Rule
	void MonsterSpawned();
	void MonsterKilled();
	int GetRemainingMonsters() const { return RemainingMonsters; }
	int GetCurrentStage() const { return CurrentStage; }

	UFUNCTION(BlueprintCallable, Category = "GameRules")
	void LevelUpPause();

	UFUNCTION(BlueprintCallable, Category = "GameRules")
	void ResumeGame();

protected:
	void InitializeUI();
	void StartNextWave();
	void MoveToNextLevel();
	void NextStage();
};