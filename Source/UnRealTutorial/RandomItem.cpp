// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomItem.h"

// Sets default values
ARandomItem::ARandomItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    TBox->SetGenerateOverlapEvents(true);
    
    //TBOX->OnComponentBeginOverlap.AddDynamic();
    
    RootComponent = TBox;
    
    SM_BOX = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    SM_BOX->AttachTo(RootComponent);
    

}

// Called when the game starts or when spawned
void ARandomItem::BeginPlay()
{
	Super::BeginPlay();
    SM_BOX->SetRelativeRotation(UKismetMathLibrary::RandomRotator());

}

// Called every frame
void ARandomItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //GetRandomRotator()
}


FRotator ARandomItem::GetRandomRotator(){
    
    FRotator MyRandomRotator = FRotator(0.0f,0.0f,0.0f);
    
    MyRandomRotator.Pitch = FMath::FRandRange(0.0f,360.0f);
    MyRandomRotator.Yaw = FMath::FRandRange(0.0f,360.0f);
    MyRandomRotator.Roll = FMath::FRandRange(0.0f,360.0f);
    
    return MyRandomRotator;
}
