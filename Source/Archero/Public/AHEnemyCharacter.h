// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHDefaultCharacter.h"
#include "AHEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API AAHEnemyCharacter : public AAHDefaultCharacter
{
	GENERATED_BODY()
public:
	AAHEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void OnDeath() override;
};
