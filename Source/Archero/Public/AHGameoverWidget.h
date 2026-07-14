// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHGameoverWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHGameoverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* MenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	// 이벤트 함수
	UFUNCTION()
	void OnMenuClicked();

	UFUNCTION()
	void OnQuitClicked();
};
