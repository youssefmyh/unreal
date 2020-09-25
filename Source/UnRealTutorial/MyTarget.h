// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine.h"
#include "MyTarget.generated.h"

UCLASS()
class UNREALTUTORIAL_API AMyTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


/*
 Shooting and Destroying Target
 */
public:
    void DestroyTarget();
    
    void Damagetarget(float Damage);
    
 
    
    
private:
    int Health;

    UTextRenderComponent* HealthText;

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* TargetStaticMesh;

    void makeTextFacePlayer();
            
};
