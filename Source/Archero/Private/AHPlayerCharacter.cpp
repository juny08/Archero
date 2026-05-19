// Fill out your copyright notice in the Description page of Project Settings.


#include "AHPlayerCharacter.h"
#include "AHEnemyCharacter.h"
#include "AHProjectile.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/OverlapResult.h"
#include "Engine/World.h"

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
}

void AAHPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    float CurrentSpeed = GetVelocity().Size();

    if (CurrentSpeed <= 0.1f)
    {
        if (!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
        {
            GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AAHPlayerCharacter::Fire, AttackDelay, true, 0.1f);
        }
    }
    else
    {
        GetWorldTimerManager().ClearTimer(AttackTimerHandle);
    }
}

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

void AAHPlayerCharacter::Fire()
{
    AAHEnemyCharacter* Target = FindNearestEnemy();

    if (ProjectileClass && Target)
    {
        FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
        SetActorRotation(FRotator(0.f, LookAtRot.Yaw, 0.f));

        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
        FRotator SpawnRotation = GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        GetWorld()->SpawnActor<AAHProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
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