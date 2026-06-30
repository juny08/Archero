// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHDefaultCharacter.h"
#include "AHSkillData.h"
#include "InputActionValue.h"
#include "AHPlayerCharacter.generated.h"

/**
 * 
 */
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

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	//class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AAHProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDelay = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RotationSpeed = 30.f;

	UPROPERTY(EditAnywhere, Category = "Skill")
	float MultiShotDelay = 0.15f;

	UPROPERTY(EditAnywhere, Category = "Status")
	float Damage = 50.f;
	//int ForwardArrowCount;
	//int MultiShotCount;

	int CurrentMultiShotCount = 0;

	bool bIsMove;

	FTimerHandle AttackTimerHandle;
	FTimerHandle MultiShotTimerHandle;

	FRotator TargetLookRotation;
	bool bIsRotatingToTarget = false;

	bool bReadyToFire = false;

	class UAHGameInstance* GI;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//
	//void Move(const FInputActionValue& Value);
	
	void Targeting();

	void Fire();

	class AAHEnemyCharacter* FindNearestEnemy();

	//void AutoTargeting();


public:
	void GainXp(float Amount);
	void AddSkill(UAHSkillData* NewSkill);
};
