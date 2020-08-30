// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnRealTutorialCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "RandomItem.generated.h"

UCLASS()
class UNREALTUTORIAL_API ARandomItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UShapeComponent *TBox;
    
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent *SM_BOX;
    
    FRotator GetRandomRotator();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    

};
