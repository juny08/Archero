// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerState.h"

void AAHPlayerState::AddXp(float Amount)
{
	currentXp += Amount;

	while (currentXp >= maxXp)
	{
		currentXp -= maxXp;
		level++;

		maxXp *= 1.2f;

		// 레벨업 이벤트 알림 (캐릭터나 UI에서 들을 수 있음)
		if (OnLevelUp.IsBound())
		{
			OnLevelUp.Broadcast(level);
		}
	}

	// XP 변경 알림 (XP 바 업데이트용)
	if (OnXPChanged.IsBound())
	{
		OnXPChanged.Broadcast(currentXp, maxXp);
	}

	UE_LOG(LogTemp, Warning, TEXT("Current Level: %d, XP: %f / %f"), level, currentXp, maxXp);
}
