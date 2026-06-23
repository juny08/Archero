// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerController.h"
#include "AHPlayerState.h"
#include "AHJoyStickWidget.h"
#include "AHLevelUpWidget.h"
#include "AHPlayWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AAHPlayerController::AAHPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAHPlayerController::BeginPlay()
{
    Super::BeginPlay();
    InitializeUI();

	if (AAHPlayerState* PS = GetPlayerState<AAHPlayerState>())
	{
		PS->OnLevelUp.AddDynamic(this, &AAHPlayerController::OnLevelUp);
	}
}

void AAHPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ApplyMovementInput(DeltaTime);
}

void AAHPlayerController::ApplyMovementInput(float DeltaTime)
{
    if (!JoystickWidgetInstance || !JoystickWidgetInstance->bIsActive) return;

    ACharacter* Char = GetCharacter();
    if (!Char) return;

    FVector2D Axis = JoystickWidgetInstance->JoystickAxis;
    if (Axis.IsNearlyZero()) return;

    FVector MoveDir = FVector(-Axis.Y, Axis.X, 0.f); // ← X↔Y 스왑

    Char->AddMovementInput(MoveDir, 1.f);

    if (!MoveDir.IsNearlyZero())
    {
        FRotator TargetRot = MoveDir.Rotation();
        Char->SetActorRotation(
            FMath::RInterpTo(Char->GetActorRotation(), TargetRot, DeltaTime, 10.f));
    }
}

#pragma region UI

void AAHPlayerController::InitializeUI()
{
	// Play Widget
	if (PlayWidgetClass)
	{
		PlayWidgetInstance = CreateWidget<UAHPlayWidget>(this, PlayWidgetClass);
		if (PlayWidgetInstance)
		{
			PlayWidgetInstance->AddToViewport(0);
		}
	}

	// Joystick
	if (JoystickWidgetClass)
	{
		JoystickWidgetInstance = CreateWidget<UAHJoyStickWidget>(this, JoystickWidgetClass);
		if (JoystickWidgetInstance)
		{
			JoystickWidgetInstance->AddToViewport(1);
		}
	}

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	//bShowMouseCursor = false;
#if PLATFORM_ANDROID || PLATFORM_IOS
	bShowMouseCursor = false;
#else
	bShowMouseCursor = true;
#endif
}

void AAHPlayerController::ShowLevelUpUI()
{
	if (!LevelUpWidgetClass) return;

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	LevelUpWidgetInstance = CreateWidget<UAHLevelUpWidget>(this, LevelUpWidgetClass);
	if (LevelUpWidgetInstance)
	{
		LevelUpWidgetInstance->AddToViewport(10);
	}

	FInputModeUIOnly Mode;
	SetInputMode(Mode);
	bShowMouseCursor = true;
}

void AAHPlayerController::HideLevelUpUI()
{
	if (LevelUpWidgetInstance)
	{
		LevelUpWidgetInstance->RemoveFromParent();
		LevelUpWidgetInstance = nullptr;
	}

	FInputModeGameAndUI Mode;
	SetInputMode(Mode);
	//bShowMouseCursor = false;
#if PLATFORM_ANDROID || PLATFORM_IOS
	bShowMouseCursor = false;
#else
	bShowMouseCursor = true;
#endif

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void AAHPlayerController::OnLevelUp(int NewLevel)
{
	ShowLevelUpUI();
}

#pragma endregion