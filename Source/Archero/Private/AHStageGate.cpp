#include "AHStageGate.h"
#include "AHGameInstance.h"
#include "AHPlayerCharacter.h"

void AAHStageGate::BeginPlay()
{
	Super::BeginPlay();
}

void AAHStageGate::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (bIsOpen)
		{
			GateClose();
			UAHGameInstance* GI = GetGameInstance<UAHGameInstance>();
			if (!GI)
			{
				return;
			}

			if (AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(OtherActor))
			{
				GI->SavePlayerRun(Player->GetPlayerStats());
			}

			FString LevelName = FString::Printf(TEXT("Stage%d"), GI->CurrentStage);
			UGameplayStatics::OpenLevel(this, FName(*LevelName));
			UE_LOG(LogTemp, Warning, TEXT("Move to Stage %d"), GI->CurrentStage);
		}
	}
}
