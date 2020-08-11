// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnRealTutorialCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Item.generated.h"

UCLASS()
class UNREALTUTORIAL_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    

public:
    UPROPERTY(EditAnywhere)
    FString itemName = FString("My Item");
    
    UShapeComponent *TBox;
    
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent *SM_TBox;
    
    AUnRealTutorialCharacter *MyPlyerController;
    
    void Pickup();
    
    bool IsItemWithRange = false;
    
    UFUNCTION()
    void TriggerEnter(class UPrimitiveComponent* Comp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    UFUNCTION()
    void TriggerExit(class UPrimitiveComponent* Comp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void SetMyPlayer(AActor * player);

    
    
    

};
