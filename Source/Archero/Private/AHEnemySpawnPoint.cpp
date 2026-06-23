// Fill out your copyright notice in the Description page of Project Settings.


#include "AHEnemySpawnPoint.h"

AAHEnemySpawnPoint::AAHEnemySpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

FVector AAHEnemySpawnPoint::GetSpawnLocation()
{
	return FVector();
}
