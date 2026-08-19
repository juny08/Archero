// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AHGate.h"
#include "AHStageGate.generated.h"

UCLASS()
class ARCHERO_API AAHStageGate : public AAHGate
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;
};
