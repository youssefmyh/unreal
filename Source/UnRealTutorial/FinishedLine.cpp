// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishedLine.h"

// Sets default values
AFinishedLine::AFinishedLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	finalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Final Object"));

	RootComponent = finalBox;

	finalBox->SetGenerateOverlapEvents(true);
	finalBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishedLine::TriggerEnter);

}

// Called when the game starts or when spawned
void AFinishedLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishedLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void AFinishedLine::TriggerEnter(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor->IsA(ACharacter::StaticClass()))
	{
		UGameplayStatics::PlaySoundAtLocation(this, MySound, GetActorLocation());
	}

}
