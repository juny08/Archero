// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHSkillLogic.h"
#include "AHForwardArrowLogic.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHForwardArrowLogic : public UAHSkillLogic
{
	GENERATED_BODY()
	
public:
	virtual void Activate_Implementation(UAHGameInstance* GI, float Value) override
    {
        GI->ForwardArrowCount += (int)Value;
    }
};
