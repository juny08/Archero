#pragma once

#include "CoreMinimal.h"
#include "AHGate.h"
#include "AHEndGate.generated.h"

UCLASS()
class ARCHERO_API AAHEndGate : public AAHGate
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;
};
