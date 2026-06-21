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
	
	public:
    // 스킬 3개를 받아서 카드 세팅
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void SetupSkillCards(const TArray<UAHSkillData*>& Skills);

    // 카드 클릭 시 BP에서 이걸 호출
    UFUNCTION(BlueprintCallable, Category = "UI")
    void OnSkillSelected(UAHSkillData* SelectedSkill);

private:
    // 어떤 스킬 풀에서 뽑을지
    UPROPERTY(EditAnywhere, Category = "Skill")
    TArray<UAHSkillData*> SkillPool;

public:
    // GameState가 이걸 호출해서 카드 세팅
    void RollRandomSkills();
};
