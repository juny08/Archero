// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameoverWidget.h"
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

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UAHGameoverWidget::OnQuitClicked);
	}
}

void UAHGameoverWidget::OnMenuClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}

void UAHGameoverWidget::OnQuitClicked()
{
	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}