// Fill out your copyright notice in the Description page of Project Settings.


#include "AHDefaultAnimInstance.h"
#include "AHDefaultCharacter.h"

void UAHDefaultAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAHDefaultAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter)
	{
		Speed = OwnerCharacter->GetVelocity().Size();
	}
}
