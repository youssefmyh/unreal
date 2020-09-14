// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTextRotator.h"
#include "UnRealTutorialCharacter.h"

// Sets default values
AMyTextRotator::AMyTextRotator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	textComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Rotating Text"));
	textComponent->SetWorldSize(70.0f);
	textComponent->SetTextRenderColor(FColor::Red);
	textComponent->SetHorizontalAlignment(EHTA_Center);

}

// Called when the game starts or when spawned
void AMyTextRotator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTextRotator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	makeTextFacePlayer();
}


void AMyTextRotator::makeTextFacePlayer() {

	AUnRealTutorialCharacter* myCharacter = Cast<AUnRealTutorialCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	FRotator MewRotation = myCharacter->GetActorRotation();
	MewRotation.Yaw += 180.0f;
	textComponent->SetRelativeRotation(MewRotation);
}
