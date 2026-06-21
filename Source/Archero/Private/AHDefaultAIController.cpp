// Fill out your copyright notice in the Description page of Project Settings.


#include "AHDefaultAIController.h"
#include "AHEnemyCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/CapsuleComponent.h"

AAHDefaultAIController::AAHDefaultAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAHDefaultAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    UpdateAI();
}

void AAHDefaultAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    // 이동 완료(도착 or 실패 모두) → 추격 상태 리셋
    // 다음 Tick에서 Distance 체크 후 필요하면 다시 StartChase 호출됨
    bIsChasing = false;
}

void AAHDefaultAIController::UpdateAI()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (!PC) return;

    APawn* Target = PC->GetPawn();
    AAHEnemyCharacter* MyEnemy = Cast<AAHEnemyCharacter>(GetPawn());
    if (!Target || !MyEnemy) return;

    float AttackRange = MyEnemy->GetAttackRange();
    float Distance = FVector::Dist(MyEnemy->GetActorLocation(), Target->GetActorLocation());

    if (Distance > AttackRange)
    {
        // 추격 중이 아닐 때만 MoveToActor 호출
        if (!bIsChasing)
        {
            StartChase(Target, AttackRange);
        }
    }
    else
    {
        // 사정거리 안 → 추격 중지 + 공격
        if (bIsChasing)
        {
            StopMovement();
            bIsChasing = false;
        }

        // 플레이어 방향으로 회전
        FVector LookDir = Target->GetActorLocation() - MyEnemy->GetActorLocation();
        LookDir.Z = 0.f;
        MyEnemy->SetActorRotation(LookDir.Rotation());

        if (bCanAttack)
        {
            Attack();
        }
    }
}

void AAHDefaultAIController::StartChase(APawn * Target, float AcceptanceRadius)
{
    bIsChasing = true;

    float MyRadius = 0.f;
    float TargetRadius = 0.f;

    if (ACharacter* MyChar = Cast<ACharacter>(GetPawn()))
        MyRadius = MyChar->GetCapsuleComponent()->GetScaledCapsuleRadius();

    if (ACharacter* TargetChar = Cast<ACharacter>(Target))
        TargetRadius = TargetChar->GetCapsuleComponent()->GetScaledCapsuleRadius();

    float AdjustedRadius = FMath::Max(0.f, AcceptanceRadius - MyRadius - TargetRadius);

    FAIMoveRequest MoveRequest;
    MoveRequest.SetGoalActor(Target);
    MoveRequest.SetAcceptanceRadius(AdjustedRadius);
    MoveRequest.SetUsePathfinding(true);
    MoveRequest.SetAllowPartialPath(false);

    MoveTo(MoveRequest);
}

void AAHDefaultAIController::Attack()
{
	AAHEnemyCharacter* MyEnemy = Cast<AAHEnemyCharacter>(GetPawn());
	APlayerController* asPlayer = GetWorld()->GetFirstPlayerController();

	if (MyEnemy && asPlayer && asPlayer->GetPawn())
	{
		bCanAttack = false;

		MyEnemy->ExecuteAttack(asPlayer->GetPawn());

		GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AAHDefaultAIController::ResetAttackCooldown, AttackCooldown, false);
	}
}

void AAHDefaultAIController::ResetAttackCooldown()
{
	bCanAttack = true;

    UpdateAI();
}
