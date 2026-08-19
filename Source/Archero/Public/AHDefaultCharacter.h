#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AHDefaultCharacter.generated.h"

UCLASS(Abstract)
class ARCHERO_API AAHDefaultCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowAbstract = "true"))
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowAbstract = "true"))
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HpBar;

public:
	AAHDefaultCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void OnDeath();

	virtual void UpdateHpBar() PURE_VIRTUAL(AAHDefaultCharacter::UpdateHpBar, );

public:	
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
