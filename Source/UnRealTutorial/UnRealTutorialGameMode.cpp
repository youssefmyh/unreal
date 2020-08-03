// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnRealTutorialGameMode.h"
#include "UnRealTutorialHUD.h"
#include "UnRealTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnRealTutorialGameMode::AUnRealTutorialGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnRealTutorialHUD::StaticClass();
}
