// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PentralMaterial.generated.h"

UCLASS()
class UNREALTUTORIAL_API APentralMaterial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APentralMaterial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    int32 Resistance;
    
    
 private:
   
    
    
UPROPERTY(EditAnywhere)
    UStaticMeshComponent * StaticMesh;
    

};
