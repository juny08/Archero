// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameInstance.h"

void UAHGameInstance::AddXp(float Amount)
{
	CurrentXp += Amount;

	while (CurrentXp >= MaxXp)
	{
		CurrentXp -= MaxXp;
		Level++;

		MaxXp *= 1.2f;

		if (OnLevelUp.IsBound())
		{
			OnLevelUp.Broadcast(Level);
		}
	}

	if (OnXPChanged.IsBound())
	{
		OnXPChanged.Broadcast(CurrentXp, MaxXp);
	}

	UE_LOG(LogTemp, Warning, TEXT("Level: %d, XP: %f / %f"), Level, CurrentXp, MaxXp);

}