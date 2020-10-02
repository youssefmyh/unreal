// Fill out your copyright notice in the Description page of Project Settings.


#include "GlowObject.h"

// Sets default values
AGlowObject::AGlowObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SM_Glow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    
    
    UProperty(EditAnywhere)
    UBoxComponent * BT_Pickup;
    
}

// Called when the game starts or when spawned
void AGlowObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlowObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

