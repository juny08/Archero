// Fill out your copyright notice in the Description page of Project Settings.


#include "AHResultWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UAHResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UAHResultWidget::OnMenuClicked);
	}
}

void UAHResultWidget::OnMenuClicked()
{
	UGameplayStatics::OpenLevel(this, FName("Menu"));
}
