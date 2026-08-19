#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AHPlayerStatsComponent.h"
#include "AHGameInstance.generated.h"

UCLASS()
class ARCHERO_API UAHGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    void SavePlayerRun(const UAHPlayerStatsComponent* PlayerStats);
    void RestorePlayerRun(UAHPlayerStatsComponent* PlayerStats) const;
    void ResetRun();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Run")
    int32 CurrentStage = 1;

private:
    UPROPERTY(Transient)
    bool bHasSavedPlayerRun = false;

    UPROPERTY(Transient)
    FAHPlayerRunData SavedPlayerRun;
};
