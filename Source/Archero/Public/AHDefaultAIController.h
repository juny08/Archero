// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AHDefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARCHERO_API AAHDefaultAIController : public AAIController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float attackCooldown = 1.5f;

	bool canAttack = true;

public:
	AAHDefaultAIController();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void Move();
	virtual void Attack();
	virtual void ResetAttackCooldown();
};
