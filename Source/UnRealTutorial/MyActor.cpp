// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	tBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	tBox->SetGenerateOverlapEvents(true);
	tBox->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::TriggerEnter);

	tBox->SetRelativeScale3D(scalingScale);
	RootComponent = tBox;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//MyMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	SpeedScale = 0.0f;

	
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

/*	FVector newLocation = GetActorLocation();
	float DeletaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	if(IsYAxis)
		newLocation.Y += DeletaHeight * SpeedScale;
	else
		newLocation.X += DeletaHeight * SpeedScale;

	RunningTime += DeltaTime;
	SetActorLocation(newLocation);*/

//	UE_LOG(LogTemp, Warning, TEXT("THE TIME IS %f   %f   %f"), RunningTime, DeltaTime , DeletaHeight);
}

void AMyActor::TriggerEnter(class UPrimitiveComponent* Comp , class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// reset player when you touch 

	UE_LOG(LogTemp,Warning,TEXT("They start pverlaping"));
	if(OtherActor->IsA(ACharacter::StaticClass()))
	OtherActor->SetActorLocation(PlayerStrtingLocation);
}
