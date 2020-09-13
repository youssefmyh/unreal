// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTarget.h"

// Sets default values
AMyTarget::AMyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    TargetStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Mesh"));
    RootComponent = TargetStaticMesh;
    Health = 100;
}

// Called when the game starts or when spawned
void AMyTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyTarget::DestroyTarget(){
    
    /*Animation*/
    Destroy();
    
}

void AMyTarget::Damagetarget(float Damage){
    
    Health -= Damage;
    
    if(Health <= 0.0f)
    {
        DestroyTarget();
    }
    
}
