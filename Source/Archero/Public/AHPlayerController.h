// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AHPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API AAHPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AAHPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

protected:
	// UI Class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UAHPlayWidget> PlayWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UAHLevelUpWidget> LevelUpWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UAHJoyStickWidget> JoystickWidgetClass;

	// UI Instance
	UPROPERTY()
	class UAHPlayWidget* PlayWidgetInstance = nullptr;

	UPROPERTY()
	class UAHJoyStickWidget* JoystickWidgetInstance = nullptr;

	UPROPERTY()
	class UAHLevelUpWidget* LevelUpWidgetInstance = nullptr;

private:
	void InitializeUI();

    // Tick에서 호출: 조이스틱 값 → 캐릭터 이동
    void ApplyMovementInput(float DeltaTime);

public:
	void ShowLevelUpUI();
	void HideLevelUpUI();

	UFUNCTION()
	void OnLevelUp(int NewLevel);
};
