// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	// 이벤트 함수
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();
};
