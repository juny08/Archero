// Fill out your copyright notice in the Description page of Project Settings.


#include "AHHpBarWidget.h"

void UAHHpBarWidget::SetHpPercent(float percent)
{
	if (HpBar)
	{
		HpBar->SetPercent(percent);
	}
}