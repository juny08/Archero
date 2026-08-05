// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AHStageGate.generated.h"

UCLASS()
class ARCHERO_API AAHStageGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAHStageGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;
	
	bool bIsOpen;

public:
	void GateOpen() { bIsOpen = true; }
	void GateClose() { bIsOpen = false; }

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

};
