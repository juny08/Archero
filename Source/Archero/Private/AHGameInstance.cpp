#include "AHGameInstance.h"

void UAHGameInstance::SavePlayerRun(const UAHPlayerStatsComponent* PlayerStats)
{
    if (!PlayerStats)
    {
        return;
    }

    SavedPlayerRun = PlayerStats->CreateRunData();
    bHasSavedPlayerRun = true;
}

void UAHGameInstance::RestorePlayerRun(UAHPlayerStatsComponent* PlayerStats) const
{
    if (bHasSavedPlayerRun && PlayerStats)
    {
        PlayerStats->ApplyRunData(SavedPlayerRun);
    }
}

void UAHGameInstance::ResetRun()
{
    CurrentStage = 1;
    bHasSavedPlayerRun = false;
    SavedPlayerRun = FAHPlayerRunData();
}
