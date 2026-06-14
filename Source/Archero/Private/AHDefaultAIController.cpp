// Fill out your copyright notice in the Description page of Project Settings.


#include "AHDefaultAIController.h"
#include "AHEnemyCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AAHDefaultAIController::AAHDefaultAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAHDefaultAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Move();
}

void AAHDefaultAIController::Move()
{
	APlayerController* asPlayer = GetWorld()->GetFirstPlayerController();
	if (!asPlayer) return;

	APawn* target = asPlayer->GetPawn();

	AAHEnemyCharacter* MyEnemy = Cast<AAHEnemyCharacter>(GetPawn());

	if (target && MyEnemy)
	{
		float attackRange = MyEnemy->GetAttackRange();
		float Distance = FVector::Dist(MyEnemy->GetActorLocation(), target->GetActorLocation());

		if (Distance > attackRange)
		{
			MoveToActor(target, attackRange);
		}
		else
		{
			StopMovement();

			FVector LookDir = target->GetActorLocation() - GetPawn()->GetActorLocation();
			LookDir.Z = 0.f;
			MyEnemy->SetActorRotation(LookDir.Rotation());

			if (canAttack)
			{
				Attack();
			}
		}
	}
}

void AAHDefaultAIController::Attack()
{
	AAHEnemyCharacter* MyEnemy = Cast<AAHEnemyCharacter>(GetPawn());
	APlayerController* asPlayer = GetWorld()->GetFirstPlayerController();

	if (MyEnemy && asPlayer && asPlayer->GetPawn())
	{
		canAttack = false;

		MyEnemy->ExecuteAttack(asPlayer->GetPawn());

		FTimerHandle CooldownTimerHandle;
		GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AAHDefaultAIController::ResetAttackCooldown, attackCooldown, false);
	}
}

void AAHDefaultAIController::ResetAttackCooldown()
{
	canAttack = true;
}
