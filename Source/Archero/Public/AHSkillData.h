

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AHSkillData.generated.h"


UENUM(BlueprintType)
enum class ESkillEffectType : uint8
{
    StatBoost,
    AddForwardArrow,
    AddMultiShot
};

UCLASS()
class ARCHERO_API UAHSkillData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill")
    FName skillName;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill")
    ESkillEffectType effectType;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill")
    float value;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill")
    UTexture2D* skillIcon;
};
