#pragma once

#include "CoreMinimal.h"
#include "AHDefaultCharacter.h"
#include "AHEnemyCharacter.generated.h"

UCLASS()
class ARCHERO_API AAHEnemyCharacter : public AAHDefaultCharacter
{
	GENERATED_BODY()

public:
	AAHEnemyCharacter();

	virtual void ExecuteAttack(AActor* AttackTarget);

	float GetAttackRange() const { return attackRange; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowAbstract = "true"))
	float HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowAbstract = "true"))
	float HealthCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowAbstract = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reward")
	float dropXp = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<class AAHProjectile> EnemyProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float attackRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float attackDamage = 10.f;

	virtual void BeginPlay() override;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	virtual void OnDeath() override;

	inline float GetHealthRate() { return HealthCurrent / HealthMax; }

	virtual void UpdateHpBar() override;
};
