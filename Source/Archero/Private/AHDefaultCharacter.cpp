// Fill out your copyright notice in the Description page of Project Settings.


#include "AHDefaultCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "AHHPBarWidget.h"

// Sets default values
AAHDefaultCharacter::AAHDefaultCharacter()
{
	// 변수 초기화
	HealthMax = 100.f;
	HealthCurrent = HealthMax;

	// InitCapsuleSize(반지름, 절반 높이)
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 카메라랑 캐릭터랑 별개로
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터가 움직이는 방향으로 몸을 자동회전
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 회전 속도 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	// z축 제한
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// HpBar
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetDrawSize(FVector2D(150.f, 20.f));
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);


	// 틱 사용
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AAHDefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


float AAHDefaultCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsValid(EventInstigator) && EventInstigator == GetController()) { return 0; } // 본인공격 무효

	HealthCurrent -= DamageAmount;
	UpdateHpBar();

	if (HealthCurrent <= 0)
	{
		OnDeath();
	}
	return DamageAmount;
}

void AAHDefaultCharacter::OnDeath()
{
	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
}

void AAHDefaultCharacter::UpdateHpBar()
{
	if (HpBar)
	{
		UAHHpBarWidget* HpWidget = Cast<UAHHpBarWidget>(HpBar->GetUserWidgetObject());
		if (HpWidget)
		{
			float Percent = HealthCurrent / HealthMax;
			HpWidget->SetHpPercent(Percent);
		}
	}
}

// Called every frame
void AAHDefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAHDefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

