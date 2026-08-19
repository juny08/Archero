#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AHPlayerStatsComponent.generated.h"

class UAHSkillData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLevelUpDelegate, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerXPChangedDelegate, float, CurrentXP, float, MaxXP);

USTRUCT()
struct ARCHERO_API FAHPlayerRunData
{
    GENERATED_BODY()

    UPROPERTY()
    int32 Level = 1;
    UPROPERTY()
    float MaxXp = 100.f;
    UPROPERTY()
    float CurrentXp = 0.f;
    UPROPERTY()
    float MaxHp = 100.f;
    UPROPERTY()
    float CurrentHp = 100.f;
    UPROPERTY()
    float AttackDamage = 50.f;
    UPROPERTY()
    float BonusDamage = 0.f;
    UPROPERTY()
    float AttackDelay = 1.f;
    UPROPERTY()
    int32 ForwardArrowCount = 1;
    UPROPERTY()
    int32 MultiShotCount = 1;
    UPROPERTY()
    bool bCanRevive = true;
    UPROPERTY()
    TArray<TObjectPtr<UAHSkillData>> Skills;
};

UCLASS(ClassGroup=(Player), meta=(BlueprintSpawnableComponent))
class ARCHERO_API UAHPlayerStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAHPlayerStatsComponent();

    void AddXp(float Amount);
    void AddSkill(UAHSkillData* NewSkill);
    bool ApplyDamage(float DamageAmount);
    bool Revive();
    void ResetStats();

    FAHPlayerRunData CreateRunData() const;
    void ApplyRunData(const FAHPlayerRunData& RunData);

    int32 GetLevel() const { return Level; }
    float GetXP() const { return CurrentXp; }
    float GetMaxXP() const { return MaxXp; }
    float GetHP() const { return CurrentHp; }
    float GetMaxHP() const { return MaxHp; }
    float GetAttackDamage() const { return AttackDamage + BonusDamage; }
    float GetAttackDelay() const { return AttackDelay; }
    int32 GetForwardArrowCount() const { return ForwardArrowCount; }
    int32 GetMultiShotCount() const { return MultiShotCount; }

    void SetHP(float Value) { CurrentHp = FMath::Clamp(Value, 0.f, MaxHp); }
    void SetAttackDelay(float Value) { AttackDelay = FMath::Max(0.1f, Value); }
    void AddBonusDamage(float Value) { BonusDamage += Value; }
    void AddForwardArrow(int32 Count) { ForwardArrowCount = FMath::Max(1, ForwardArrowCount + Count); }
    void AddMultiShot(int32 Count) { MultiShotCount = FMath::Max(1, MultiShotCount + Count); }

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerLevelUpDelegate OnLevelUp;
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerXPChangedDelegate OnXPChanged;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float InitialMaxHp = 100.f;
    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float InitialAttackDamage = 50.f;
    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    float InitialAttackDelay = 1.f;

    UPROPERTY(VisibleAnywhere, Category = "Stats")
    int32 Level = 1;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float MaxXp = 100.f;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float CurrentXp = 0.f;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float MaxHp = 100.f;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float CurrentHp = 100.f;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float AttackDamage = 50.f;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float BonusDamage = 0.f;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float AttackDelay = 1.f;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    int32 ForwardArrowCount = 1;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    int32 MultiShotCount = 1;
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    bool bCanRevive = true;
    UPROPERTY(VisibleAnywhere, Category = "Skill")
    TArray<TObjectPtr<UAHSkillData>> Skills;
};
