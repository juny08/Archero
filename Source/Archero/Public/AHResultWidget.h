// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHResultWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* MenuButton;

	UFUNCTION()
	void OnMenuClicked();
};
