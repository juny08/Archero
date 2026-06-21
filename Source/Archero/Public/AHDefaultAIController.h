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
	UPROPERTY(EditAnywhere, Category = "AI")
	float AttackCooldown = 1.5f;

	bool bCanAttack = true;
	bool bIsChasing = false;

	FTimerHandle CooldownTimerHandle;

public:
	AAHDefaultAIController();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	virtual void UpdateAI();
	virtual void StartChase(APawn* Target, float AcceptanceRadius);
	virtual void Attack();
	virtual void ResetAttackCooldown();
};
