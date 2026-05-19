// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArcheroGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AArcheroGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	AArcheroGameMode();
};



