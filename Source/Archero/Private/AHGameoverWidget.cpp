// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameoverWidget.h"
#include "AHGameInstance.h"
#include "AHPlayerController.h"
#include "AHPlayerCharacter.h"
#include "AHPlayerStatsComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UAHGameoverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UAHGameoverWidget::OnMenuClicked);
	}

	if (ReviveButton)
	{
		ReviveButton->OnClicked.AddDynamic(this, &UAHGameoverWidget::OnReviveClicked);
	}

	if (ReStartButton)
	{
		ReStartButton->OnClicked.AddDynamic(this, &UAHGameoverWidget::OnReStartClicked);
	}
}

void UAHGameoverWidget::OnMenuClicked()
{
	if (UAHGameInstance* GameInstance = GetGameInstance<UAHGameInstance>())
	{
		GameInstance->ResetRun();
	}

	UGameplayStatics::OpenLevel(this, FName("Menu"));
}

void UAHGameoverWidget::OnReviveClicked()
{
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetOwningPlayer());
	AAHPlayerCharacter* Player = PC ? Cast<AAHPlayerCharacter>(PC->GetPawn()) : nullptr;
	if (!Player) return;

	if (Player->GetPlayerStats()->Revive())
	{
		Player->UpdateHpBar();
		PC->HideGameoverUI();
	}
}

void UAHGameoverWidget::OnReStartClicked()
{
	UAHGameInstance* GI = GetGameInstance<UAHGameInstance>();
	if (GI)
	{
		GI->ResetRun();
	}

	UGameplayStatics::OpenLevel(this, FName("Stage1"));
}
