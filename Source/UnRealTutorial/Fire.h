// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnRealTutorialCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Fire.generated.h"

UCLASS()
class UNREALTUTORIAL_API AFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UShapeComponent* TB_Fire;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SM_Fire;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* PS_Fire;

	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	AUnRealTutorialCharacter* currentPlayerController;

	void SetCurrentPlayer(AActor* myPlayer);

	UPROPERTY(EditAnywhere)
		FString helpText = FString(TEXT("Press F to Activate the Fire"));

	int32 ResetTimer = 3;


	bool bPlayerWithinRange = false;
	bool bFireLit = false;
	void Light();
	void AdvanceTimer();
	void TimerHasFinished();

	FTimerHandle CounterDownTimerHandle;

};