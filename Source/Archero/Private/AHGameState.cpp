// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameState.h"

AAHGameState::AAHGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentStage = 1;
	CurrentWave = 1;
	RemainingMonsters = 0;
}