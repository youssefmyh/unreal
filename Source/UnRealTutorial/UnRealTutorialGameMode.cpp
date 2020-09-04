// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnRealTutorialGameMode.h"
#include "UnRealTutorialHUD.h"
#include "UnRealTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

AUnRealTutorialGameMode::AUnRealTutorialGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnRealTutorialHUD::StaticClass();
}

void AUnRealTutorialGameMode::BeginPlay(){
    
    Super::BeginPlay();
    
    AUnRealTutorialCharacter * tutorialCharacter = Cast<AUnRealTutorialCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
    
    if(PlayerHUDClass != nullptr){
        
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
        CurrentWidget->AddToViewport();
    }
}
