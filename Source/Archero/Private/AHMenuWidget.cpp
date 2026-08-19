// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMenuWidget.h"
#include "AHGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UAHMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UAHMenuWidget::OnStartClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UAHMenuWidget::OnQuitClicked);
	}
}

void UAHMenuWidget::OnStartClicked()
{
	if (UAHGameInstance* GameInstance = GetGameInstance<UAHGameInstance>())
	{
		GameInstance->ResetRun();
	}

	UGameplayStatics::OpenLevel(this, FName("Stage1"));
}

void UAHMenuWidget::OnQuitClicked()
{
	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}
