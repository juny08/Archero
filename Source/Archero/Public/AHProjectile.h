// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHProjectile.generated.h"

UCLASS()
class ARCHERO_API AAHProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAHProjectile();
	
public:
	UPROPERTY(EditAnywhere, Category = "Status")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Status")
	float InitialSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxSpeed = 2000.f;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
