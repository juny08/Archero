// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "AHPlayerCharacter.h"
#include "AHPlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API UAHPlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//class AAHDefaultGameState* currentState = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class AAHPlayerCharacter* currentCharacter = nullptr;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* XpBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelText;

	void TryBindPlayerState();
	FTimerHandle BindingTimerHandle;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UFUNCTION()
	void UpdateLevel(int NewLevel);

	UFUNCTION()
	void UpdateXp(float CurrentXp, float MaxXp);
};
