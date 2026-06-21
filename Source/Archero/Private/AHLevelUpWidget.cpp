// Fill out your copyright notice in the Description page of Project Settings.


#include "AHLevelUpWidget.h"
#include "AHPlayerCharacter.h"
#include "AHGameState.h"
#include "Kismet/GameplayStatics.h"

void UAHLevelUpWidget::OnSkillSelected(UAHSkillData * SelectedSkill)
{
    if (!SelectedSkill) return;

    // 플레이어에게 스킬 추가
    if (AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(
        UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
    {
        Player->AddSkill(SelectedSkill);
    }

    // 게임 재개
    if (AAHGameState* GS = GetWorld()->GetGameState<AAHGameState>())
    {
        GS->ResumeGame();
    }
}

void UAHLevelUpWidget::RollRandomSkills()
{
    if (SkillPool.Num() == 0) return;

    // 풀에서 중복 없이 최대 3개 뽑기
    TArray<UAHSkillData*> Shuffled = SkillPool;

    // Fisher-Yates 셔플
    for (int32 i = Shuffled.Num() - 1; i > 0; i--)
    {
        int32 j = FMath::RandRange(0, i);
        Shuffled.Swap(i, j);
    }

    // 앞에서 3개만 자르기
    int32 Count = FMath::Min(3, Shuffled.Num());
    TArray<UAHSkillData*> RolledSkills;
    for (int32 i = 0; i < Count; i++)
    {
        RolledSkills.Add(Shuffled[i]);
    }

    // BP에 전달 → 카드 UI 세팅
    SetupSkillCards(RolledSkills);
}
