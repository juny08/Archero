// Fill out your copyright notice in the Description page of Project Settings.


#include "AHEnemyCharacter.h"
#include "AHDefaultAIController.h"
#include "Components/CapsuleComponent.h"

AAHEnemyCharacter::AAHEnemyCharacter()
{
	HealthMax = 50.f;
	HealthCurrent = HealthMax;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	AIControllerClass = AAHDefaultAIController::StaticClass();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAHEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAHEnemyCharacter::OnDeath()
{
	Super::OnDeath();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //충돌 끄기

	SetLifeSpan(0.1f); //일정시간 후 사라지기
}
