// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraUtility::ACameraUtility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraUtility::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraUtility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    /*
	const float TimeBetweenCameraChange = 3.0f;
	const float SmoothBlendTime = 0.75f;

	timeBetweenCameraCheck -= DeltaTime;

	if (timeBetweenCameraCheck <= 0.0f) {
	
		timeBetweenCameraCheck = TimeBetweenCameraChange;

		APlayerController* ourPlayer = UGameplayStatics::GetPlayerController(this, 0);

		if (!ourPlayer)
			return;
		
		if (cameraTwo && ourPlayer->GetViewTarget() == cameraOne) {
			ourPlayer->SetViewTargetWithBlend(cameraTwo, SmoothBlendTime);
		
		}
		else {

			ourPlayer->SetViewTarget(cameraOne);

		}
	}
     */


}

