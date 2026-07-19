// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHPauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* MenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UFUNCTION()
	void OnMenuClicked();

	UFUNCTION()
	void OnResumeClicked();
};
