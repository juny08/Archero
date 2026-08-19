#include "AHEnemyCharacter.h"
#include "AHPlayerCharacter.h"
#include "AHDefaultAIController.h"
#include "AHWaveManager.h"
#include "AHProjectile.h"
#include "AHHPBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

AAHEnemyCharacter::AAHEnemyCharacter()
{
	HealthMax = 50.f;
	HealthCurrent = HealthMax;
	MoveSpeed = 300.f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	AIControllerClass = AAHDefaultAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAHEnemyCharacter::ExecuteAttack(AActor* AttackTarget)
{
	if (!AttackTarget) return;

	// 원거리
	if (EnemyProjectileClass)
	{
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
		FRotator SpawnRotation = GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AAHProjectile* Projectile = GetWorld()->SpawnActor<AAHProjectile>(EnemyProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (Projectile)
		{
			Projectile->Damage = attackDamage;
		}
	}
	// 근거리
	else
	{
		UGameplayStatics::ApplyDamage(AttackTarget, attackDamage, GetController(), this, UDamageType::StaticClass());
	}
}

void AAHEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

float AAHEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsValid(EventInstigator) && EventInstigator == GetController()) { return 0; } // 본인공격 무효

	HealthCurrent -= DamageAmount;
	UpdateHpBar();

	if (HealthCurrent <= 0)
	{
		OnDeath();
	}
	return DamageAmount;
}

void AAHEnemyCharacter::OnDeath()
{
	Super::OnDeath();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //충돌 끄기

	if (AAHPlayerCharacter* player = Cast<AAHPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		player->GainXp(dropXp);
	}

	if (AAHWaveManager* WM = Cast<AAHWaveManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAHWaveManager::StaticClass())))
	{
		WM->OnEnemyKilled();
	}

	SetLifeSpan(0.1f); //일정시간 후 사라지기
}

void AAHEnemyCharacter::UpdateHpBar()
{
	if (HpBar)
	{
		UAHHpBarWidget* HpWidget = Cast<UAHHpBarWidget>(HpBar->GetUserWidgetObject());
		if (HpWidget)
		{
			float Percent = HealthCurrent / HealthMax;
			HpWidget->SetHpPercent(Percent);
		}
	}
}