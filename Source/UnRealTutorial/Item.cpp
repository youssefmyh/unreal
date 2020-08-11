// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    TBox->SetGenerateOverlapEvents(true);
    TBox->OnComponentBeginOverlap.AddDynamic(this,&AItem::TriggerEnter);
    TBox->OnComponentEndOverlap.AddDynamic(this,&AItem::TriggerExit);
    RootComponent = TBox;
    
    SM_TBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
    SM_TBox->AttachTo(RootComponent);
    
}


void AItem::SetMyPlayer(AActor* player) {

    MyPlyerController = Cast<AUnRealTutorialCharacter>(player);

}
// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (MyPlyerController != NULL) {
    
        if (MyPlyerController->bIsPickingUp && IsItemWithRange) {
        
            Pickup();
        }

    }

}


void AItem::TriggerEnter(class UPrimitiveComponent* Comp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
    
    IsItemWithRange = true;
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("Click on E to collect item"));
    SetMyPlayer(OtherActor);
}

void AItem::TriggerExit(class UPrimitiveComponent* Comp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
    
    IsItemWithRange = false;
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("item Exit of Range"));
    
}


void AItem::Pickup(){
    
    MyPlyerController->Inventory.Add(itemName);
    Destroy();

    
}
