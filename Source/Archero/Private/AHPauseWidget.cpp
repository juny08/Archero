// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPauseWidget.h"
#include "AHPlayerController.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UAHPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UAHPauseWidget::OnMenuClicked);
	}

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UAHPauseWidget::OnResumeClicked);
	}
}

void UAHPauseWidget::OnMenuClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}

void UAHPauseWidget::OnResumeClicked()
{
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetOwningPlayer());
	if (!PC) return;

	PC->HidePauseUI();
}