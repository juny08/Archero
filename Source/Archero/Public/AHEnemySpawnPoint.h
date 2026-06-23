#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHEnemySpawnPoint.generated.h"

UCLASS()
class ARCHERO_API AAHEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AAHEnemySpawnPoint();

	FVector GetSpawnLocation() const { return GetActorLocation(); }
};
