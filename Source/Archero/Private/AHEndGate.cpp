#include "AHEndGate.h"
#include "AHPlayerCharacter.h"
#include "AHPlayerController.h"

void AAHEndGate::BeginPlay()
{
	Super::BeginPlay();
}

void AAHEndGate::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsOpen) return;

	if (AAHPlayerCharacter* Player = Cast<AAHPlayerCharacter>(OtherActor))
	{
		GateClose();
		if (AAHPlayerController* PC = Cast<AAHPlayerController>(Player->GetController()))
		{
			PC->ShowResultUI();
		}
	}
}
