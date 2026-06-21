// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AHJoyStickWidget.generated.h"

// 조이스틱 입력값을 외부로 전달하는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJoystickInput, FVector2D, InputAxis);

UCLASS()
class ARCHERO_API UAHJoyStickWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // PlayerController가 매 Tick마다 읽어갈 값
    UPROPERTY(BlueprintReadOnly, Category = "Joystick")
    FVector2D JoystickAxis = FVector2D::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category = "Joystick")
    bool bIsActive = false;

protected:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
    virtual FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
    virtual FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;

    // PC환경 (테스트용)
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    // BP에서 썸 이미지 위치 업데이트용
    UFUNCTION(BlueprintImplementableEvent, Category = "Joystick")
    void OnAxisUpdated(FVector2D Axis);

private:
    UPROPERTY(EditAnywhere, Category = "Joystick", meta = (AllowPrivateAccess = "true"))
    float JoystickRadius = 80.f;

    FVector2D TouchOrigin = FVector2D::ZeroVector;

    void UpdateAxis(const FGeometry& InGeometry, FVector2D CurrentPos);

    // 터치/마우스 공통 로직
    void OnInputStart(const FGeometry& InGeometry, FVector2D ScreenPos);
    void OnInputMove(const FGeometry& InGeometry, FVector2D ScreenPos);
    void OnInputEnd();
};
