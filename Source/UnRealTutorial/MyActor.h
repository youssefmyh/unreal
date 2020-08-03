// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UNREALTUTORIAL_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* tBox;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MyMesh;
	

	UPROPERTY(EditAnywhere)
		float SpeedScale = 0.0f;

	float RunningTime;

	UPROPERTY(EditAnywhere)
		bool IsYAxis;

	UFUNCTION()
     	void TriggerEnter(class UPrimitiveComponent* Comp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector PlayerStrtingLocation = FVector(-151.0f, 501.0f, 235.0f);
	FVector scalingScale = FVector(.5f,.5f,0.5f);
};
