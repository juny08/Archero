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

private:
    UPROPERTY()
    class UAHJoyStickWidget* JoystickWidget = nullptr;

    // BeginPlay에서 GameState → 조이스틱 참조 획득
    void CacheJoystickWidget();

    // Tick에서 호출: 조이스틱 값 → 캐릭터 이동
    void ApplyMovementInput(float DeltaTime);
};
