// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHSkillLogic.h"
#include "AHMultiShotLogic.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHMultiShotLogic : public UAHSkillLogic
{
	GENERATED_BODY()
	
public:
    virtual void Activate_Implementation(UAHGameInstance* GI, float Value) override
    {
        GI->MultiShotCount += (int)Value;
    }
};
