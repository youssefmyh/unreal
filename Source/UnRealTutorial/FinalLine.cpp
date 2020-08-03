// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalLine.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AFinalLine::AFinalLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	finishLineBox = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box"));
	finishLineBox->SetGenerateOverlapEvents(true);
	finishLineBox->OnComponentBeginOverlap.AddDynamic(this, &AFinalLine::TriggerEnter);

	//finishLineBox->set
}

// Called when the game starts or when spawned
void AFinalLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinalLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFinalLine::TriggerEnter(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor->IsA(ACharacter::StaticClass()))
	{	

//		OtherActor->PlaySound(MySound);

	}


}
