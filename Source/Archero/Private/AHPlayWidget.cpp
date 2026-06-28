// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayWidget.h"
#include "AHPlayerState.h"
#include "AHGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UAHPlayWidget::TryBindPlayerState()
{
	//APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//if (!PC) return;
	//
	//AAHPlayerState* PS = PC->GetPlayerState<AAHPlayerState>();

	UAHGameInstance* GI = GetGameInstance<UAHGameInstance>();

	if (GI)
	{
		// PlayerState의 델리게이트와 위젯의 함수를 연결!
		GI->OnLevelUp.AddDynamic(this, &UAHPlayWidget::UpdateLevel);
		GI->OnXPChanged.AddDynamic(this, &UAHPlayWidget::UpdateXp);

		// 처음 켜졌을 때의 초기값 반영
		UpdateLevel(GI->GetLevel());
		UpdateXp(GI->GetXP(), 100.f);

		// 연결 성공했으므로 타이머 해제
		GetWorld()->GetTimerManager().ClearTimer(BindingTimerHandle);
	}
}

void UAHPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetWorld()->GetTimerManager().SetTimer(
		BindingTimerHandle,
		this,
		&UAHPlayWidget::TryBindPlayerState,
		0.1f,
		true
	);

	XpBar = CastChecked<UProgressBar>(GetWidgetFromName(TEXT("XpBar")));
}

void UAHPlayWidget::NativeTick(const FGeometry & MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (IsValid(XpBar) /*&& IsValid(currentState)*/)
	{
		//XpBar->SetPercent(currentCharacter->);
	}
}

void UAHPlayWidget::UpdateLevel(int NewLevel)
{
	if (LevelText)
	{
		LevelText->SetText(FText::Format(FText::FromString("Lv. {0}"), NewLevel));
	}
}

void UAHPlayWidget::UpdateXp(float CurrentXp, float MaxXp)
{
	if (XpBar && MaxXp > 0.f)
	{
		float Percent = CurrentXp / MaxXp;
		XpBar->SetPercent(Percent);
	}
}
