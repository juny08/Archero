// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AHGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPChangedDelegate, float, CurrentXP, float, MaxXP);

class UAHSkillData;

UCLASS()
class ARCHERO_API UAHGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void AddXp(float Amount);
	void AddSkill(UAHSkillData* NewSkill);

	// === Getter ===
	int GetLevel() const { return Level; }
	float GetXP() const { return CurrentXp; }
	float GetMaxXP() const { return MaxXp; }

public:
	// === 이벤트 ===
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpDelegate OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnXPChangedDelegate OnXPChanged;

public:
	//UPROPERTY(EditAnywhere, Category = "Skill")
	//TArray<UAHSkillData*> InitialSkills;
	//
	//UPROPERTY(VisibleAnywhere, Category = "Skill")
	//TArray<UAHSkillData*> ActiveSkills;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	TArray<UAHSkillData*> Skills;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentXp = 0.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxXp = 100.f;

public:
	int CurrentStage = 1;
	int ForwardArrowCount = 1;
	int MultiShotCount = 1;
	float AttackDamage = 50.f;
	int LevelUpCount = 0;
};
