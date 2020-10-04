// Fill out your copyright notice in the Description page of Project Settings.


#include "GlowObject.h"

// Sets default values
AGlowObject::AGlowObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SM_Glow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    BT_Pickup = CreateDefaultSubobject<UBoxComponent>(TEXT("BT Pickup"));
    BT_Pickup->SetGenerateOverlapEvents(true);
    BT_Pickup->OnComponentBeginOverlap.AddDynamic(this,&AGlowObject::EnterObjectRasuis);
    BT_Pickup->OnComponentEndOverlap.AddDynamic(this,&AGlowObject::ExitObjectRaduis);

    
//    UProperty(EditAnywhere)
//    UBoxComponent * BT_Pickup;
    
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

void AGlowObject::EnterObjectRasuis(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("Enter Glow Raduis"));
    ToggleGlow(true);
}

void AGlowObject::ExitObjectRaduis(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ToggleGlow(false);
    GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,TEXT("Exit Glow Raduis"));

}


void AGlowObject::ToggleGlow(bool IsGlowing){
    
    SM_Glow->SetRenderCustomDepth(IsGlowing);
    
}

