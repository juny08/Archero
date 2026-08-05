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
    virtual void Activate_Implementation(UAHGameInstance* GI, float Value) override
    {
        if (GI->AttackDelay <= 0.5f) return;
        GI->SetAttackDelay(GI->AttackDelay - Value);
    }
};
