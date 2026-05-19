// Fill out your copyright notice in the Description page of Project Settings.


#include "AHDefaultGameState.h"

AAHDefaultGameState::AAHDefaultGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAHDefaultGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AAHDefaultGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
