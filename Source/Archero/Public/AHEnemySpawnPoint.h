#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AHEnemyCharacter.h"
#include "AHEnemySpawnPoint.generated.h"

UCLASS()
class ARCHERO_API AAHEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AAHEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int SpawnWave = 1;

public:	
	AAHEnemySpawnPoint();

	FVector GetSpawnLocation() const { return GetActorLocation(); }


};
