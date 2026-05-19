// Fill out your copyright notice in the Description page of Project Settings.


#include "AHDefaultAIController.h"
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
	APawn* target = asPlayer->GetPawn();

	if (asPlayer && target)
	{
		float Distance = FVector::Dist(GetPawn()->GetActorLocation(), target->GetActorLocation());

		if (Distance > attackRange)
		{
			MoveToActor(target, attackRange);
		}
		else
		{
			StopMovement();

			FVector LookDir = target->GetActorLocation() - GetPawn()->GetActorLocation();
			LookDir.Z = 0.f; // 위아래로 기울어짐 방지
			GetPawn()->SetActorRotation(LookDir.Rotation());
		}
	}
}
