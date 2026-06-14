// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AHDefaultCharacter.generated.h"

UCLASS(Abstract)
class ARCHERO_API AAHDefaultCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowAbstract = "true"))
	float HealthMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowAbstract = "true"))
	float HealthCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowAbstract = "true"))
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowAbstract = "true"))
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HpBar;

public:
	// Sets default values for this character's properties
	AAHDefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnDeath();

	void UpdateHpBar();

public:	
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	inline float GetHealthRate() { return HealthCurrent / HealthMax; }
};
