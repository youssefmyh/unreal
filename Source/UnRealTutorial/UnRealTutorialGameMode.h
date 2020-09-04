// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnRealTutorialGameMode.generated.h"

UCLASS(minimalapi)
class AUnRealTutorialGameMode : public AGameModeBase
{
	GENERATED_BODY()

    virtual void BeginPlay() override;
    
public:
	AUnRealTutorialGameMode();
    
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "Stamina" , Meta = (BlueprintProtected = "true"))
    TSubclassOf<class UUserWidget> PlayerHUDClass;
    
    UPROPERTY()
    class UUserWidget * CurrentWidget;
    
};



