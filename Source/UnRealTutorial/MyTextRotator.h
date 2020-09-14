// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "MyTextRotator.generated.h"

UCLASS()
class UNREALTUTORIAL_API AMyTextRotator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTextRotator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Create Text 
	UTextRenderComponent* textComponent;

	/* Configure Text while the player is moving*/
	void makeTextFacePlayer();
};
