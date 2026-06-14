// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AHPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPChangedDelegate, float, CurrentXP, float, MaxXP);

UCLASS()
class ARCHERO_API AAHPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void AddXp(float Amount);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    int level = 1;

    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float currentXp = 0.f;

    UPROPERTY(EditAnywhere, Category = "Stats")
    float maxXp = 100.f;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpDelegate OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnXPChangedDelegate OnXPChanged;

	int GetLevel() const { return level; }
	float GetXP() const { return currentXp; }
};
