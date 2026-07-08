// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHEnemyCharacter.h"
#include "AHBossCharacter.generated.h"


UENUM()
enum class EBossAttackState : uint8
{
	Idle,
	Charging_Dash,
	Charging_Fan,
	Charging_Laser,
	Executing
};

UCLASS()
class ARCHERO_API AAHBossCharacter : public AAHEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AAHBossCharacter();

	virtual void ExecuteAttack(AActor* AttackTarget) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// 상태
	EBossAttackState CurrentState = EBossAttackState::Idle;

	// 타겟
	UPROPERTY()
	AActor* CurrentTarget;

	// 방향 고정 (중요)
	FVector CachedDirection;

	// 타이머
	FTimerHandle ChargeTimer;

	// 설정값
	UPROPERTY(EditAnywhere, Category = "Boss")
	float ChargeTime = 1.5f;

	// 대쉬 관련
	bool bIsDashing = false;

	FVector DashStart;
	FVector DashEnd;

	float DashDuration = 0.3f;
	float DashElapsed = 0.f;

	// 대쉬 충돌 판정용
	UPROPERTY(EditAnywhere, Category = "Boss")
	float DashHitRadius = 80.f;

	UPROPERTY()
	TSet<AActor*> DashDamagedActors; // 이미 데미지 준 액터 기록

	float CachedMaxWalkSpeed = 0.f;

protected:
	// 패턴 시작
	void StartDashCharge();
	void StartFanCharge();
	void StartLaserCharge();

	// 실행
	void ExecuteDash();
	void ExecuteFanAttack();
	void FireLaser();

	// 움직임 제어
	void FreezeMovement();
	void UnfreezeMovement();

	// 상태 초기화
	void ResetState();

};
