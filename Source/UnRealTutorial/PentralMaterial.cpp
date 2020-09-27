// Fill out your copyright notice in the Description page of Project Settings.


#include "PentralMaterial.h"

// Sets default values
APentralMaterial::APentralMaterial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Resistance = 2;
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

}

// Called when the game starts or when spawned
void APentralMaterial::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APentralMaterial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

