// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AHPlayerStatsComponent.h"
#include "AHSkillLogic.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ARCHERO_API UAHSkillLogic : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Activate(UAHPlayerStatsComponent* PlayerStats, float Value);
};
