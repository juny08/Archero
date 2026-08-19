// Fill out your copyright notice in the Description page of Project Settings.


#include "AHGameMode.h"
#include "AHPlayerCharacter.h"
#include "AHPlayerController.h"
#include "AHGameState.h"
#include "UObject/ConstructorHelpers.h"

AAHGameMode::AAHGameMode()
{
	PlayerControllerClass = AAHPlayerController::StaticClass();
	GameStateClass = AAHGameState::StaticClass();


	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ArcHero/Blueprints/BP_AHPlayer.BP_AHPlayer_C"));

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
