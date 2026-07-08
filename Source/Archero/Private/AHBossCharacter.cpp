// Fill out your copyright notice in the Description page of Project Settings.


#include "AHBossCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "AHProjectile.h"
#include "Engine/OverlapResult.h"
#include "AHDefaultAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AAHBossCharacter::AAHBossCharacter()
{
	HealthMax = 300.f;
	HealthCurrent = HealthMax;
}

void AAHBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAHBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDashing)
	{
		DashElapsed += DeltaTime;
		float Alpha = FMath::Clamp(DashElapsed / DashDuration, 0.f, 1.f);

		FVector NewLocation = FMath::Lerp(DashStart, DashEnd, Alpha);

		// 스윕 없이 순수 이동 (플레이어 캡슐 뚫고 지나감)
		SetActorLocation(NewLocation, false);

		// 데미지는 별도 오버랩 체크로 판정
		TArray<FOverlapResult> Overlaps;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		bool bHit = GetWorld()->OverlapMultiByChannel(
			Overlaps,
			GetActorLocation(),
			FQuat::Identity,
			ECC_Pawn,
			FCollisionShape::MakeSphere(DashHitRadius),
			Params
		);

		if (bHit)
		{
			for (const FOverlapResult& Result : Overlaps)
			{
				AActor* HitActor = Result.GetActor();
				if (HitActor && !DashDamagedActors.Contains(HitActor))
				{
					DashDamagedActors.Add(HitActor);

					UGameplayStatics::ApplyDamage(
						HitActor,
						attackDamage,
						GetController(),
						this,
						UDamageType::StaticClass()
					);
				}
			}
		}

		if (Alpha >= 1.f)
		{
			bIsDashing = false;
			UnfreezeMovement();
			ResetState();
		}
	}
}

void AAHBossCharacter::ExecuteAttack(AActor* AttackTarget)
{
	if (!AttackTarget || CurrentState != EBossAttackState::Idle) return;

	CurrentTarget = AttackTarget;

	// 방향 고정 (핵심)
	CachedDirection = (AttackTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	int Pattern = FMath::RandRange(0, 2);

	switch (Pattern)
	{
	case 0: StartDashCharge(); break;
	case 1: StartFanCharge(); break;
	case 2: StartLaserCharge(); break;
	}
}

#pragma region Dash

void AAHBossCharacter::StartDashCharge()
{
	CurrentState = EBossAttackState::Charging_Dash;

	FreezeMovement();

	DrawDebugLine(GetWorld(),
		GetActorLocation(),
		GetActorLocation() + CachedDirection * 1000.f,
		FColor::Red,
		false,
		ChargeTime,
		0,
		100.f);

	GetWorldTimerManager().SetTimer(ChargeTimer, this, &AAHBossCharacter::ExecuteDash, ChargeTime, false);
}

void AAHBossCharacter::ExecuteDash()
{
	CurrentState = EBossAttackState::Executing;

	bIsDashing = true;
	DashDamagedActors.Empty(); // 새 대쉬 시작할 때 초기화

	DashStart = GetActorLocation();
	DashEnd = DashStart + CachedDirection * 800.f;

	DashElapsed = 0.f;
}

#pragma endregion

#pragma region FanAttack

void AAHBossCharacter::StartFanCharge()
{
	CurrentState = EBossAttackState::Charging_Fan;

	for (int i = -3; i <= 3; i++)
	{
		FRotator Rot = CachedDirection.Rotation();
		Rot.Yaw += i * 10.f;

		FVector Dir = Rot.Vector();

		DrawDebugLine(GetWorld(),
			GetActorLocation(),
			GetActorLocation() + Dir * 800.f,
			FColor::Red,
			false,
			ChargeTime,
			0,
			4.f);
	}

	GetWorldTimerManager().SetTimer(ChargeTimer, this, &AAHBossCharacter::ExecuteFanAttack, ChargeTime, false);
}

void AAHBossCharacter::ExecuteFanAttack()
{
	CurrentState = EBossAttackState::Executing;

	for (int i = -3; i <= 3; i++)
	{
		FRotator Rot = CachedDirection.Rotation();
		Rot.Yaw += i * 10.f;

		AAHProjectile* Proj = GetWorld()->SpawnActor<AAHProjectile>(
			EnemyProjectileClass,
			GetActorLocation(),
			Rot
		);

		if (Proj)
		{
			Proj->Damage = attackDamage;
		}
	}

	ResetState();
}

#pragma endregion

#pragma region Laser

void AAHBossCharacter::StartLaserCharge()
{
	CurrentState = EBossAttackState::Charging_Laser;

	FVector Start = GetActorLocation();
	FVector End = Start + CachedDirection * 1200.f;

	DrawDebugLine(GetWorld(),
		Start,
		End,
		FColor::Red,
		false,
		ChargeTime,
		0,
		8.f);

	GetWorldTimerManager().SetTimer(ChargeTimer, this, &AAHBossCharacter::FireLaser, ChargeTime, false);
}

void AAHBossCharacter::FireLaser()
{
	CurrentState = EBossAttackState::Executing;

	FVector Start = GetActorLocation();
	FVector End = Start + CachedDirection * 1200.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params))
	{
		if (Hit.GetActor())
		{
			UGameplayStatics::ApplyDamage(
				Hit.GetActor(),
				attackDamage * 3.f,
				GetController(),
				this,
				UDamageType::StaticClass()
			);
		}
	}

	// 🔵 실제 발사
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 0.2f, 0, 10.f);

	ResetState();
}

#pragma endregion

void AAHBossCharacter::FreezeMovement()
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		CachedMaxWalkSpeed = Movement->MaxWalkSpeed;
		Movement->MaxWalkSpeed = 0.f;
		Movement->StopMovementImmediately(); // 관성 남아있는 것도 즉시 정지
	}

	// AI가 MoveTo 등으로 계속 이동 명령을 내리는 구조라면
	// 컨트롤러의 경로 이동도 멈춰줘야 합니다.
	if (AAHDefaultAIController* AI = Cast<AAHDefaultAIController>(GetController()))
	{
		AI->StopMovement();
	}
}

void AAHBossCharacter::UnfreezeMovement()
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->MaxWalkSpeed = CachedMaxWalkSpeed;
	}
}

void AAHBossCharacter::ResetState()
{
	CurrentState = EBossAttackState::Idle;
}