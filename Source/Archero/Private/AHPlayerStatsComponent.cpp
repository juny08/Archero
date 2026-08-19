#include "AHPlayerStatsComponent.h"
#include "AHSkillData.h"
#include "AHSkillLogic.h"

UAHPlayerStatsComponent::UAHPlayerStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    ResetStats();
}

void UAHPlayerStatsComponent::AddXp(float Amount)
{
    CurrentXp += Amount;
    while (CurrentXp >= MaxXp)
    {
        CurrentXp -= MaxXp;
        ++Level;
        MaxXp *= 1.2f;
        OnLevelUp.Broadcast(Level);
    }
    OnXPChanged.Broadcast(CurrentXp, MaxXp);
}

void UAHPlayerStatsComponent::AddSkill(UAHSkillData* NewSkill)
{
    if (!NewSkill || !NewSkill->SkillLogicClass)
    {
        return;
    }

    Skills.Add(NewSkill);
    if (UAHSkillLogic* Logic = NewObject<UAHSkillLogic>(this, NewSkill->SkillLogicClass))
    {
        Logic->Activate(this, NewSkill->value);
    }
}

bool UAHPlayerStatsComponent::ApplyDamage(float DamageAmount)
{
    SetHP(CurrentHp - DamageAmount);
    return CurrentHp <= 0.f;
}

bool UAHPlayerStatsComponent::Revive()
{
    if (!bCanRevive)
    {
        return false;
    }
    bCanRevive = false;
    CurrentHp = MaxHp;
    return true;
}

void UAHPlayerStatsComponent::ResetStats()
{
    Level = 1;
    MaxXp = 100.f;
    CurrentXp = 0.f;
    MaxHp = InitialMaxHp;
    CurrentHp = MaxHp;
    AttackDamage = InitialAttackDamage;
    BonusDamage = 0.f;
    AttackDelay = InitialAttackDelay;
    ForwardArrowCount = 1;
    MultiShotCount = 1;
    bCanRevive = true;
    Skills.Empty();
}

FAHPlayerRunData UAHPlayerStatsComponent::CreateRunData() const
{
    FAHPlayerRunData RunData;
    RunData.Level = Level;
    RunData.MaxXp = MaxXp;
    RunData.CurrentXp = CurrentXp;
    RunData.MaxHp = MaxHp;
    RunData.CurrentHp = CurrentHp;
    RunData.AttackDamage = AttackDamage;
    RunData.BonusDamage = BonusDamage;
    RunData.AttackDelay = AttackDelay;
    RunData.ForwardArrowCount = ForwardArrowCount;
    RunData.MultiShotCount = MultiShotCount;
    RunData.bCanRevive = bCanRevive;
    RunData.Skills = Skills;
    return RunData;
}

void UAHPlayerStatsComponent::ApplyRunData(const FAHPlayerRunData& RunData)
{
    Level = RunData.Level;
    MaxXp = RunData.MaxXp;
    CurrentXp = RunData.CurrentXp;
    MaxHp = RunData.MaxHp;
    CurrentHp = RunData.CurrentHp;
    AttackDamage = RunData.AttackDamage;
    BonusDamage = RunData.BonusDamage;
    AttackDelay = RunData.AttackDelay;
    ForwardArrowCount = RunData.ForwardArrowCount;
    MultiShotCount = RunData.MultiShotCount;
    bCanRevive = RunData.bCanRevive;
    Skills = RunData.Skills;
    OnXPChanged.Broadcast(CurrentXp, MaxXp);
}
