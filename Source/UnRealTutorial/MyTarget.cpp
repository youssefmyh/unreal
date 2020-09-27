// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTarget.h"
#include "UnRealTutorialCharacter.h"
// Sets default values
AMyTarget::AMyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Health = 100;


    HealthText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Health Text"));
    HealthText->SetWorldSize(20.0f);
    HealthText->SetTextRenderColor(FColor::Red);
    HealthText->HorizontalAlignment=EHTA_Center;
    TargetStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Mesh"));

    //RootComponent = TargetStaticMesh;


}

// Called when the game starts or when spawned
void AMyTarget::BeginPlay()
{
	Super::BeginPlay();

    HealthText->SetText(FString::Printf(TEXT("Heath : %d"), Health));
}

// Called every frame
void AMyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    makeTextFacePlayer();
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
    else {

        HealthText->SetText(FString::Printf(TEXT("Heath : %d"), Health));
    }
}

void AMyTarget::makeTextFacePlayer()
{
    AUnRealTutorialCharacter* chracter = Cast<AUnRealTutorialCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
    FRotator NewRotation = chracter->GetActorRotation();
    NewRotation.Yaw += 180.0f;
    HealthText->SetRelativeRotation(NewRotation);
}
