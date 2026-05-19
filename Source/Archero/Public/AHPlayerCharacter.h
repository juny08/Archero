// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHDefaultCharacter.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AAHProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDelay = 0.5f;

	bool IsMove;

	FTimerHandle AttackTimerHandle;



	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	
	void Fire();

	class AAHEnemyCharacter* FindNearestEnemy();

	//void AutoTargeting();

};
