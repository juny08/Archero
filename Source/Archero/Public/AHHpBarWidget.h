// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "AHHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HpBar;

	void SetHpPercent(float percent);
};
