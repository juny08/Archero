// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHSkillData.h"
#include "AHLevelUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHLevelUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
    // 어떤 스킬 풀에서 뽑을지
    UPROPERTY(EditAnywhere, Category = "Skill")
    TArray<UAHSkillData*> SkillPool;

public:
    // BP에서 세팅
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void SetupSkillCards(const TArray<UAHSkillData*>& Skills);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnSkillSelected(UAHSkillData* SelectedSkill);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void RollRandomSkills();
};
