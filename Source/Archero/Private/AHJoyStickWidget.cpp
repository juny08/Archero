// Fill out your copyright notice in the Description page of Project Settings.


#include "AHJoyStickWidget.h"

void UAHJoyStickWidget::NativeConstruct()
{
    Super::NativeConstruct();
    SetIsFocusable(true); // 터치 이벤트 수신 필수
}

#pragma region Mobile

FReply UAHJoyStickWidget::NativeOnTouchStarted(
    const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
    OnInputStart(InGeometry, InGestureEvent.GetScreenSpacePosition());
    return FReply::Handled().CaptureMouse(GetCachedWidget().ToSharedRef());
}

FReply UAHJoyStickWidget::NativeOnTouchMoved(
    const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
    OnInputMove(InGeometry, InGestureEvent.GetScreenSpacePosition());
    return FReply::Handled();
}

FReply UAHJoyStickWidget::NativeOnTouchEnded(
    const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
    OnInputEnd();
    return FReply::Handled().ReleaseMouseCapture();
}

#pragma endregion

#pragma region PC

FReply UAHJoyStickWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
        return FReply::Unhandled();

    OnInputStart(InGeometry, InMouseEvent.GetScreenSpacePosition());
    // 위젯 밖으로 마우스가 나가도 Move/Up 이벤트 계속 수신
    return FReply::Handled().CaptureMouse(GetCachedWidget().ToSharedRef());
}

FReply UAHJoyStickWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    OnInputMove(InGeometry, InMouseEvent.GetScreenSpacePosition());
    return FReply::Handled();
}

FReply UAHJoyStickWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == false)
        return FReply::Unhandled();

    OnInputEnd();
    return FReply::Handled().ReleaseMouseCapture();
}

#pragma endregion

void UAHJoyStickWidget::UpdateAxis(const FGeometry& InGeometry, FVector2D CurrentPos)
{
    FVector2D Delta = CurrentPos - TouchOrigin;
    float Distance = Delta.Size();

    if (Distance > JoystickRadius)
        Delta = Delta / Distance * JoystickRadius;

    JoystickAxis = Delta / JoystickRadius;
    JoystickAxis.Y = -JoystickAxis.Y; // 화면 Y → 월드 Y 반전

    OnAxisUpdated(JoystickAxis);
}

#pragma region PC & Mobile

void UAHJoyStickWidget::OnInputStart(const FGeometry& InGeometry, FVector2D ScreenPos)
{
    bIsActive = true;
    TouchOrigin = InGeometry.AbsoluteToLocal(ScreenPos);

    // 시작 시엔 축 값이 0 → 썸 위치 초기화
    JoystickAxis = FVector2D::ZeroVector;
    OnAxisUpdated(JoystickAxis);
}

void UAHJoyStickWidget::OnInputMove(const FGeometry & InGeometry, FVector2D ScreenPos)
{
    if (!bIsActive) return;

    FVector2D CurrentPos = InGeometry.AbsoluteToLocal(ScreenPos);
    FVector2D Delta = CurrentPos - TouchOrigin;
    float Distance = Delta.Size();

    if (Distance > JoystickRadius)
        Delta = Delta / Distance * JoystickRadius;

    JoystickAxis = Delta / JoystickRadius;

    OnAxisUpdated(JoystickAxis);
}

void UAHJoyStickWidget::OnInputEnd()
{
    bIsActive = false;
    JoystickAxis = FVector2D::ZeroVector;
    OnAxisUpdated(JoystickAxis);
}

#pragma endregion