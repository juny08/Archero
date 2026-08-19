#pragma region Header

#include "AHPlayerCharacter.h"
#include "AHEnemyCharacter.h"
#include "AHProjectile.h"
#include "AHGameInstance.h"
#include "AHPlayerStatsComponent.h"
#include "AHHPBarWidget.h"
#include "AHPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/OverlapResult.h"
#include "Engine/World.h"

#include "Components/WidgetComponent.h"

#pragma endregion

#pragma region Init

AAHPlayerCharacter::AAHPlayerCharacter()
{
    PlayerStats = CreateDefaultSubobject<UAHPlayerStatsComponent>(TEXT("PlayerStats"));

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 1500.f;
    CameraBoom->SetRelativeRotation(FRotator(-65.f, 0.f, 0.f));
    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;
    CameraBoom->bDoCollisionTest = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AAHPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    PlayerStats->ResetStats();
    if (UAHGameInstance* GameInstance = GetGameInstance<UAHGameInstance>())
    {
        GameInstance->RestorePlayerRun(PlayerStats);
    }

    UpdateHpBar();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
		if (AAHPlayerController* ArcheroPlayerController = Cast<AAHPlayerController>(PlayerController))
		{
			ArcheroPlayerController->BindPlayerStats(PlayerStats);
		}

        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
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
            GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AAHPlayerCharacter::Targeting, PlayerStats->GetAttackDelay(), true, 0.1f);
        }
    }
    else
    {
        GetWorldTimerManager().ClearTimer(AttackTimerHandle);
    }
}

#pragma region Fire

void AAHPlayerCharacter::Targeting()
{
    
    AAHEnemyCharacter* Target = FindNearestEnemy();
    if (Target)
    {
        FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
        
        TargetLookRotation = FRotator(0.f, LookAtRot.Yaw, 0.f);
        bIsRotatingToTarget = true;

        bReadyToFire = true;
    }
}

void AAHPlayerCharacter::Fire()
{
    if (!ProjectileClass) return;

    // --- 전방 화살 로직 ---
    float ArrowInterval = 30.f; // 화살 사이의 가로 간격 (유닛 단위)

    const int32 ForwardArrowCount = PlayerStats->GetForwardArrowCount();
    for (int32 i = 0; i < ForwardArrowCount; i++)
    {
        const float CenterOffset = (ForwardArrowCount - 1) * 0.5f;
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

        AAHProjectile* Projectile = GetWorld()->SpawnActor<AAHProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (Projectile)
        {
            Projectile->Damage = PlayerStats->GetAttackDamage();
        }
    }

    // --- 멀티샷 예약 ---
    CurrentMultiShotCount++;

    if (CurrentMultiShotCount < PlayerStats->GetMultiShotCount())
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
    
    // 내 주변의 Pawn 채널을 가진 물체만 감지
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

#pragma endregion

float AAHPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (IsValid(EventInstigator) && EventInstigator == GetController()) { return 0; }

    const bool bIsDead = PlayerStats->ApplyDamage(DamageAmount);
    UpdateHpBar();

    if (bIsDead)
    {
        OnDeath();
    }
    return DamageAmount;
}

void AAHPlayerCharacter::OnDeath()
{
    if (DeathMontage)
    {
        PlayAnimMontage(DeathMontage);
    }
    AAHPlayerController* PC = Cast<AAHPlayerController>(GetController());
    PC->ShowGameoverUI();
}

void AAHPlayerCharacter::UpdateHpBar()
{
    if (HpBar)
    {
        UAHHpBarWidget* HpWidget = Cast<UAHHpBarWidget>(HpBar->GetUserWidgetObject());
        if (HpWidget)
        {
            float Percent = PlayerStats->GetHP() / PlayerStats->GetMaxHP();
            HpWidget->SetHpPercent(Percent);
        }
    }
}

void AAHPlayerCharacter::GainXp(float Amount)
{
    PlayerStats->AddXp(Amount);
}
