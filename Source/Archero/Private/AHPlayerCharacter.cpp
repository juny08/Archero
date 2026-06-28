// Fill out your copyright notice in the Description page of Project Settings.

#pragma region Header

#include "AHPlayerCharacter.h"
#include "AHEnemyCharacter.h"
#include "AHProjectile.h"
//#include "AHPlayerState.h"
#include "AHGameInstance.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/OverlapResult.h"
#include "Engine/World.h"

#pragma endregion

#pragma region Init

AAHPlayerCharacter::AAHPlayerCharacter()
{
    HealthMax = 100.f;
    HealthCurrent = HealthMax;

    // 스프링 암
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 1000.f;
    CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;

    CameraBoom->bDoCollisionTest = false; // 장애물에 의한 카메라 줌 방지


    // 카메라
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false; // 암의 회전을 따르지 않음
}

void AAHPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    for (UAHSkillData* Skill : InitialSkills)
    {
        if (Skill)
        {
            AddSkill(Skill);
        }
    }
}

#pragma endregion

void AAHPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsRotatingToTarget)
    {
        // 현재 회전에서 목표 회전까지 부드럽게 이어주는 함수
        FRotator CurrentRot = GetActorRotation();
        FRotator SmoothRot = FMath::RInterpTo(CurrentRot, TargetLookRotation, DeltaTime, RotationSpeed);

        SetActorRotation(SmoothRot);

        if (bReadyToFire && CurrentRot.Equals(TargetLookRotation, 5.f))
        {
            bReadyToFire = false;
            CurrentMultiShotCount = 0;
            Fire();
        }

        if (CurrentRot.Equals(TargetLookRotation, 1.f))
        {
            bIsRotatingToTarget = false;
        }
    }

    float CurrentSpeed = GetVelocity().Size();

    if (CurrentSpeed <= 0.1f)
    {
        if (!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
        {
            GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AAHPlayerCharacter::Targeting, AttackDelay, true, 0.1f);
        }
    }
    else
    {
        GetWorldTimerManager().ClearTimer(AttackTimerHandle);
    }
}

#pragma region 다른 클래스로 이동 예정

void AAHPlayerCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* MoveComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        MoveComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAHPlayerCharacter::Move);
    }
}

void AAHPlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

#pragma endregion

#pragma region Fire

void AAHPlayerCharacter::Targeting()
{
    
    AAHEnemyCharacter* Target = FindNearestEnemy();
    if (Target)
    {
        FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
        
        //SetActorRotation(FRotator(0.f, LookAtRot.Yaw, 0.f)); <- 화면 끊김의 원인이었음
        
        TargetLookRotation = FRotator(0.f, LookAtRot.Yaw, 0.f);
        bIsRotatingToTarget = true;

        bReadyToFire = true;
    }
}

// AI
void AAHPlayerCharacter::Fire()
{
    if (!ProjectileClass) return;

    // --- 전방 화살 로직 ---
    float ArrowInterval = 30.f; // 화살 사이의 가로 간격 (유닛 단위)

    for (int i = 0; i < ForwardArrowCount; i++)
    {
        float CenterOffset = (ForwardArrowCount - 1) * 0.5f;
        float SideOffset = (i - CenterOffset) * ArrowInterval;

        // 현재 캐릭터가 바라보는 정면을 기준으로 스폰 위치와 방향 계산
        FVector SpawnLocation = GetActorLocation()
            + (GetActorForwardVector() * 100.f)
            + (GetActorRightVector() * SideOffset);

        FRotator SpawnRotation = GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        GetWorld()->SpawnActor<AAHProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
    }

    // --- 멀티샷 예약 ---
    CurrentMultiShotCount++;

    if (CurrentMultiShotCount < MultiShotCount)
    {
        GetWorldTimerManager().SetTimer(
            MultiShotTimerHandle,
            this,
            &AAHPlayerCharacter::Fire,
            MultiShotDelay,
            false
        );
    }
}

AAHEnemyCharacter* AAHPlayerCharacter::FindNearestEnemy()
{
    TArray<FOverlapResult> OverlapResults;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(1500.f); // 사거리 1500 유닛
    
    // 내 주변의 Pawn 채널을 가진 물체만 감지 (성능 훨씬 좋음)
    bool bHasFound = GetWorld()->OverlapMultiByChannel(
        OverlapResults, 
        GetActorLocation(), 
        FQuat::Identity, 
        ECollisionChannel::ECC_Pawn, 
        Sphere
    );

    AAHEnemyCharacter* NearestEnemy = nullptr;
    float MinDistance = 1500.f;

    for (auto& Result : OverlapResults)
    {
        AAHEnemyCharacter* Enemy = Cast<AAHEnemyCharacter>(Result.GetActor());
        if (Enemy)
        {
            float Distance = GetDistanceTo(Enemy);
            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                NearestEnemy = Enemy;
            }
        }
    }
    return NearestEnemy;
}

//void AAHPlayerCharacter::AutoTargeting()
//{
//    AAHEnemyCharacter* Target = FindNearestEnemy();
//    
//    if (IsValid(Target))
//    {
//        FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
//        SetActorRotation(FRotator(0.f, LookAtRot.Yaw, 0.f));
//    }
//}

#pragma endregion

void AAHPlayerCharacter::AddSkill(UAHSkillData* NewSkill)
{
    if (!NewSkill) return;

    ActiveSkills.Add(NewSkill);

    switch (NewSkill->effectType)
    {
    case ESkillEffectType::AddForwardArrow:
        ForwardArrowCount += NewSkill->value;
        break;
    case ESkillEffectType::AddMultiShot:
        MultiShotCount += NewSkill->value;
        break;
    }
}

void AAHPlayerCharacter::GainXp(float Amount)
{
    if (UAHGameInstance* GI = GetGameInstance<UAHGameInstance>())
    {
        GI->AddXp(Amount);
    }
}
