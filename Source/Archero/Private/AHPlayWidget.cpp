// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayWidget.h"
#include "AHPlayerController.h"
#include "AHPlayerStatsComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UAHPlayWidget::TryBindPlayerStats()
{
	if (AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		UAHPlayerStatsComponent* PlayerStats = Player->GetPlayerStats();
		PlayerStats->OnLevelUp.AddDynamic(this, &UAHPlayWidget::UpdateLevel);
		PlayerStats->OnXPChanged.AddDynamic(this, &UAHPlayWidget::UpdateXp);

		UpdateLevel(PlayerStats->GetLevel());
		UpdateXp(PlayerStats->GetXP(), PlayerStats->GetMaxXP());

		GetWorld()->GetTimerManager().ClearTimer(BindingTimerHandle);
	}

	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UAHPlayWidget::OnPauseClicked);
	}
}

void UAHPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetWorld()->GetTimerManager().SetTimer(
		BindingTimerHandle,
		this,
		&UAHPlayWidget::TryBindPlayerStats,
		0.1f,
		true
	);

	XpBar = CastChecked<UProgressBar>(GetWidgetFromName(TEXT("XpBar")));
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

void UAHPlayWidget::OnPauseClicked()
{
	AAHPlayerController* PC = Cast<AAHPlayerController>(GetOwningPlayer());
	if (!PC) return;

	PC->ShowPauseUI();
}
