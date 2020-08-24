// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire.h"

// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TB_Fire = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TB_Fire->SetGenerateOverlapEvents(true);
	TB_Fire->OnComponentBeginOverlap.AddDynamic(this, &AFire::TriggerEnter);
	TB_Fire->OnComponentEndOverlap.AddDynamic(this, &AFire::TriggerExit);
	TB_Fire->SetRelativeScale3D(FVector(3.0f, 3.0f, 1.0f));
	RootComponent = TB_Fire;

	SM_Fire = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire Mesh"));
	SM_Fire->AttachTo(RootComponent);


	PS_Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Partical System"));
	PS_Fire->AttachTo(RootComponent);

	PS_Fire->SetVisibility(false);

	ResetTimer = 10;

}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CounterDownTimerHandle, this, &AFire::AdvanceTimer,1.0f,true);
	PS_Fire->SetVisibility(false);
	
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentPlayerController != NULL) {

		if (currentPlayerController->bIsInteraction && bPlayerWithinRange && currentPlayerController->Inventory.Contains("Matches")&&!bFireLit) {

			Light();
		}
	
	}

}


void AFire::TriggerEnter(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bPlayerWithinRange = true;
	SetCurrentPlayer(OtherActor);

	if (bFireLit)
		return;

	if (!currentPlayerController->Inventory.Contains("Matches")) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("You don't have Matches"));

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Clieck on E to Activate the item"));

	}
}

void AFire::TriggerExit(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("Leaving the item"));

	bPlayerWithinRange = false;
}


void AFire::Light() {

	int32 XpGained = FMath::RandRange(10,100);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("You Light the fire and gain % xp"), XpGained));
	currentPlayerController->Inventory.RemoveSingle("Matches");
	bFireLit = true;
	PS_Fire->SetVisibility(true);

}
void AFire::AdvanceTimer() {
	if (bFireLit) {
		ResetTimer--;

		if (ResetTimer < 1)
		{
			TimerHasFinished();
		}
	}


}


void AFire::TimerHasFinished() {
	PS_Fire->SetVisibility(false);
	bFireLit = false;
	ResetTimer = 10.0;
}

void AFire::SetCurrentPlayer(AActor* myPlayer) {

	currentPlayerController = Cast<AUnRealTutorialCharacter>(myPlayer);

}
