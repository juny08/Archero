// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AHMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API AAHMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> MenuWidgetClass;

	UPROPERTY()
	UUserWidget* MenuWidgetInstance;
};
