// Fill out your copyright notice in the Description page of Project Settings.


#include "AHMenuPlayerController.h"
#include "Blueprint/UserWidget.h"

void AAHMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		MenuWidgetInstance = CreateWidget(this, MenuWidgetClass);

		if (MenuWidgetInstance)
		{
			MenuWidgetInstance->AddToViewport();

			// UI 입력 모드
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(MenuWidgetInstance->TakeWidget());
			SetInputMode(InputMode);
		}
	}

	// 마우스 (테스트용)
	bShowMouseCursor = true;

	// 모바일 터치
	bEnableTouchEvents = true;
	bEnableClickEvents = true;
}
