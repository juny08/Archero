// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AHGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPChangedDelegate, float, CurrentXP, float, MaxXP);

UCLASS()
class ARCHERO_API UAHGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void AddXp(float Amount);

	// === Getter ===
	int GetLevel() const { return Level; }
	float GetXP() const { return CurrentXp; }
	float GetMaxXP() const { return MaxXp; }

public:
	// === 이벤트 ===
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpDelegate OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnXPChangedDelegate OnXPChanged;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentXp = 0.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxXp = 100.f;

public:
	int CurrentStage = 1;
};
