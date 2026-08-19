#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AHGate.generated.h"

UCLASS(abstract)
class ARCHERO_API AAHGate : public AActor
{
	GENERATED_BODY()
	
public:	
	AAHGate();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	bool bIsOpen;

public:
	void GateOpen() { bIsOpen = true; }
	void GateClose() { bIsOpen = false; }

public:
	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
