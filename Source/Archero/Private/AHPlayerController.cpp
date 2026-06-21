// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerController.h"
#include "AHGameState.h"
#include "AHJoyStickWidget.h"
#include "AHPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AAHPlayerController::AAHPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAHPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // GameState가 UI를 먼저 초기화하므로 한 프레임 뒤에 참조를 가져옴
    FTimerHandle TempHandle;
    GetWorldTimerManager().SetTimer(TempHandle, this,
        &AAHPlayerController::CacheJoystickWidget, 0.1f, false);
}

void AAHPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ApplyMovementInput(DeltaTime);
}

void AAHPlayerController::CacheJoystickWidget()
{
    AAHGameState* GS = GetWorld()->GetGameState<AAHGameState>();
    if (GS)
    {
        JoystickWidget = GS->GetJoystickWidget();
    }
}

void AAHPlayerController::ApplyMovementInput(float DeltaTime)
{
    if (!JoystickWidget || !JoystickWidget->bIsActive) return;

    ACharacter* Char = GetCharacter();
    if (!Char) return;

    FVector2D Axis = JoystickWidget->JoystickAxis;
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