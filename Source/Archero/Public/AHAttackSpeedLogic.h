// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHSkillLogic.h"
#include "AHAttackSpeedLogic.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHAttackSpeedLogic : public UAHSkillLogic
{
	GENERATED_BODY()

public:
    virtual void Activate_Implementation(UAHPlayerStatsComponent* PlayerStats, float Value) override
    {
        if (!PlayerStats || PlayerStats->GetAttackDelay() <= 0.5f) return;
        PlayerStats->SetAttackDelay(PlayerStats->GetAttackDelay() - Value);
    }
};
