// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameInstance.h"
#include "AHSkillData.h"

void UAHGameInstance::AddXp(float Amount)
{
	CurrentXp += Amount;

	while (CurrentXp >= MaxXp)
	{
		CurrentXp -= MaxXp;
		Level++;

		MaxXp *= 1.2f;

		// 레벨업 이벤트 알림 (캐릭터나 UI에서 들을 수 있음)
		if (OnLevelUp.IsBound())
		{
			OnLevelUp.Broadcast(Level);
		}
	}

	// XP 변경 알림 (XP 바 업데이트용)
	if (OnXPChanged.IsBound())
	{
		OnXPChanged.Broadcast(CurrentXp, MaxXp);
	}

	UE_LOG(LogTemp, Warning, TEXT("Level: %d, XP: %f / %f"), Level, CurrentXp, MaxXp);

}

void UAHGameInstance::AddSkill(UAHSkillData* NewSkill)
{
	if (!NewSkill) return;

	Skills.Add(NewSkill);

	switch (NewSkill->effectType)
	{
	case ESkillEffectType::AddForwardArrow:
		ForwardArrowCount += NewSkill->value;
		break;
	case ESkillEffectType::AddMultiShot:
		MultiShotCount += NewSkill->value;
		break;
	//case ESkillEffectType::StatBoost:
	//	 += NewSkill->value;
	//	break;
	}
}