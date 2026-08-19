#pragma once

#include "CoreMinimal.h"
#include "AHDefaultCharacter.h"
#include "InputActionValue.h"
#include "AHPlayerCharacter.generated.h"

UCLASS()
class ARCHERO_API AAHPlayerCharacter : public AAHDefaultCharacter
{
	GENERATED_BODY()
public:
    AAHPlayerCharacter();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AAHProjectile> ProjectileClass;

public:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float RotationSpeed = 30.f;

	UPROPERTY(EditAnywhere, Category = "Skill")
	float MultiShotDelay = 0.15f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	class UAHPlayerStatsComponent* PlayerStats;

	int CurrentMultiShotCount = 0;

	bool bIsMove;

	FTimerHandle AttackTimerHandle;
	FTimerHandle MultiShotTimerHandle;

	FRotator TargetLookRotation;
	bool bIsRotatingToTarget = false;

	bool bReadyToFire = false;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	void Targeting();

	void Fire();

	class AAHEnemyCharacter* FindNearestEnemy();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	virtual void OnDeath() override;

public:
	UAHPlayerStatsComponent* GetPlayerStats() const { return PlayerStats; }

	virtual void UpdateHpBar() override;
	void GainXp(float Amount);
};
