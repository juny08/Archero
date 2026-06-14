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

	void ExecuteAttack(AActor* AttackTarget);

	float GetAttackRange() const { return attackRange; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reward")
	float dropXp = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<class AAHProjectile> EnemyProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float attackRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float attackDamage = 10.f;

	virtual void BeginPlay() override;

	virtual void OnDeath() override;
};
