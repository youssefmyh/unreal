// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlowObject.generated.h"

UCLASS()
class UNREALTUTORIAL_API AGlowObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlowObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void EnterObjectRasuis(class UPrimitiveComponent* Comp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
    UFUNCTION()
    void ExitObjectRaduis(class UPrimitiveComponent* Comp,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
protected:
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent *SM_Glow;
    
    
    UProperty(EditAnywhere)
    UBoxComponent * BT_Pickup;
    
    
    
    
    
    
    
};
