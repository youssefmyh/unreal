// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraUtility.generated.h"

UCLASS()
class UNREALTUTORIAL_API ACameraUtility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraUtility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		AActor* cameraOne;


	UPROPERTY(EditAnywhere)
		AActor* cameraTwo;

	float timeBetweenCameraCheck;

};
