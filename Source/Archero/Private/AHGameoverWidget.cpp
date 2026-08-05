// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameoverWidget.h"
#include "AHGameInstance.h"
#include "AHPlayerController.h"
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
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}

void UAHGameoverWidget::OnReviveClicked()
{
	UAHGameInstance* GI = GetGameInstance<UAHGameInstance>();
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetOwningPlayer());
	if (!GI || !PC) return;

	if(GI->Revive()) PC->HideGameoverUI();
}

void UAHGameoverWidget::OnReStartClicked()
{
	UAHGameInstance* GI = GetGameInstance<UAHGameInstance>();
	GI->StatsReset();

	UGameplayStatics::OpenLevel(this, FName("Stage1"));
}
