// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnRealTutorialCharacter.h"
#include "UnRealTutorialProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "MySaveGame.h"
#include "MyTarget.h"
#include "PentralMaterial.h"
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AUnRealTutorialCharacter

AUnRealTutorialCharacter::AUnRealTutorialCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;


	/*
	Inital Stamina
	*/
	InitialStamina = 100.0f;
	CurrentStamina = InitialStamina;

}

void AUnRealTutorialCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
    // Make Sure to use the World Location
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUnRealTutorialCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

    //Bind RayCasting Action
    
    PlayerInputComponent->BindAction("RayCast",IE_Pressed,this,&AUnRealTutorialCharacter::PerformRayCasting);
    
    
    //Bind Save and Load Game
    
    PlayerInputComponent->BindAction("Save",IE_Pressed,this,&AUnRealTutorialCharacter::SaveGame);
    PlayerInputComponent->BindAction("Load",IE_Pressed,this,&AUnRealTutorialCharacter::LoadGame);
    
	//Bind Interact
    
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AUnRealTutorialCharacter::BeginInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AUnRealTutorialCharacter::EndInteract);

	//Bind Sprint 

	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this, &AUnRealTutorialCharacter::BeginSprint);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&AUnRealTutorialCharacter::EndSprint);


    // Pickup and show Inventory
    
    PlayerInputComponent->BindAction("Pickup",IE_Pressed,this,&AUnRealTutorialCharacter::BeginPickup);
    
    PlayerInputComponent->BindAction("Pickup",IE_Released,this,&AUnRealTutorialCharacter::EndPickUp);
    
    PlayerInputComponent->BindAction("ShowInventory",IE_Pressed,this,&AUnRealTutorialCharacter::ShowInventory);
    
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUnRealTutorialCharacter::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUnRealTutorialCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnRealTutorialCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnRealTutorialCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnRealTutorialCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnRealTutorialCharacter::LookUpAtRate);
}

void AUnRealTutorialCharacter::OnFire()
{
	// try and fire a projectile

	//Initialize HitResult Array
	TArray<FHitResult> HitResults;
	HitResults.Init(FHitResult(ForceInit),10);

	FVector StartTraceVector = FirstPersonCameraComponent->GetComponentLocation();
	FVector FrowardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector EndTraceVector = (FrowardVector * 2000.0f) + StartTraceVector;

	FCollisionQueryParams *TraceParams = new FCollisionQueryParams();
	TraceParams->bTraceComplex = false;
	FCollisionResponseParams fResponseParams(ECollisionResponse::ECR_Overlap);


	// Perform Line Trace 
	bool isLineTrace = GetWorld()->LineTraceMultiByChannel(HitResults, StartTraceVector, EndTraceVector, ECC_Visibility, *TraceParams, fResponseParams);

	int32 DamageAmount = 30;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,FString::Printf(TEXT(" Bullet hole N = %d %d") , HitResults.Num(), isLineTrace));

	/*If we hist something we will create bullet hole*/
	if (HitResults.Num() > 0) {

		createBulletHole(&HitResults[0]);
	}

	// Process Each Hit Result in Our Array
	for (int x = 0; x< HitResults.Num(); x++)
	{
		AStaticMeshActor* PotentionalSolidMaterial = Cast<AStaticMeshActor>(HitResults[x].Actor.Get());

		if (PotentionalSolidMaterial != NULL && !PotentionalSolidMaterial->IsPendingKill()) {
			break;

		}
        
        
        // Check if we hit penetrable material
        
        APentralMaterial *PentralMaterialObj = Cast<APentralMaterial>(HitResults[x].Actor.Get());
        
        if(PentralMaterialObj != NULL && !PentralMaterialObj->IsPendingKill()){
            
            DamageAmount = DamageAmount / PentralMaterialObj->Resistance;
        }

        
        // check if we hit target appy damage
        AMyTarget *myTarget = Cast<AMyTarget>(HitResults[x].Actor.Get());
        
        if(myTarget != NULL && !myTarget->IsPendingKill()){
        
            myTarget->Damagetarget(DamageAmount);
            
        }
	}


	if (isLineTrace) {
	
	}





	DrawDebugLine(GetWorld(), StartTraceVector, EndTraceVector, FColor::Red, false, 5.0f);

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
    
    
   /* FHitResult * HitResult = new FHitResult();
    FVector startTarace = FirstPersonCameraComponent->GetComponentLocation();
    FVector ForwardTrace = FirstPersonCameraComponent->GetForwardVector();
    FVector EndTrace = ((ForwardTrace * 2000.0f) + startTarace);
    FCollisionQueryParams * TraceParams = new FCollisionQueryParams();
    
    if(GetWorld()->LineTraceSingleByChannel(*HitResult,startTarace,EndTrace,ECC_Visibility,*TraceParams))
    {
        
        DrawDebugLine(GetWorld(), startTarace, EndTrace, FColor::Green,false,5.0f);
        
        AMyTarget *Mytarget = Cast<AMyTarget>(HitResult->Actor.Get());
        
        if(Mytarget != NULL ){
            
            Mytarget->Damagetarget(50.0f);
            
            
        }
        
    }
	*/
    
    
    

    
    
}

void AUnRealTutorialCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUnRealTutorialCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AUnRealTutorialCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AUnRealTutorialCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AUnRealTutorialCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
        
		AddMovementInput(GetActorForwardVector(), bIsSprinting?  Value : Value/2);
        
	}
}

void AUnRealTutorialCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), bIsSprinting?  Value : Value/2);
	}
}

void AUnRealTutorialCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnRealTutorialCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AUnRealTutorialCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUnRealTutorialCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AUnRealTutorialCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AUnRealTutorialCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}

float AUnRealTutorialCharacter::GetCurrentStamina()
{
	return CurrentStamina;
}

float AUnRealTutorialCharacter::GetInitialStamina()
{
	return InitialStamina;
}

void AUnRealTutorialCharacter::UpdateCurrentStamina(float Stamina)
{
	CurrentStamina += Stamina;
}

void AUnRealTutorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCurrentStamina(-DeltaTime *0.01f * InitialStamina);
}


void AUnRealTutorialCharacter::BeginSprint() {

	bIsSprinting = true;
    GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,TEXT("Start Sprint"));
}
void AUnRealTutorialCharacter::EndSprint() {

	bIsSprinting = false;
    
    GEngine->AddOnScreenDebugMessage(-1,10,FColor::Red,TEXT("End Sprint"));

}


void AUnRealTutorialCharacter::BeginPickup(){
    
    bIsPickingUp = true;
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("Start Pickup"));
    
}

void AUnRealTutorialCharacter::EndPickUp(){

   bIsPickingUp = false;
   GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("End Pickup"));
    
}
void AUnRealTutorialCharacter::ShowInventory(){
    
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("Show Inventory"));
	for (auto & item: Inventory) {

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("items %s"),*item));

	}


}


void AUnRealTutorialCharacter::BeginInteract() {

	bIsInteraction = true;
}

void AUnRealTutorialCharacter::EndInteract() {

	bIsInteraction = false;
}


void AUnRealTutorialCharacter::SaveGame(){
    
    // Create A save Game Static Object
    UMySaveGame *saveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    
    // Get the Player Location
    saveGame->PlayerLocation = this->GetActorLocation();
    
    // Save the Game Needed The Save Game Instance and Slot Name
    // Slot name is just a Unquie Id
    UGameplayStatics::SaveGameToSlot(saveGame,TEXT("MySlot"),0);
    
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("Save Game"));
}
void AUnRealTutorialCharacter::LoadGame(){

    // Get the Load Game Instance
    UMySaveGame *loadGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

    // Load Saved MySlot whiched Saved in SaveGame
    loadGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"),0));
    
    // Set Current Player Location
    this->SetActorLocation(loadGame->PlayerLocation);
    
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("Load Game"));
}


void AUnRealTutorialCharacter::PerformRayCasting()
{

	FHitResult* HitResult = new FHitResult();
	FVector startTrace = FirstPersonCameraComponent->GetComponentLocation();
	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector EndTrace = ((ForwardVector * 5000.0f) + startTrace);

	FCollisionQueryParams* TraceParam = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, startTrace, EndTrace, ECC_Visibility, *TraceParam)) {
	
		DrawDebugLine(GetWorld(), startTrace, EndTrace, FColor::Red, true);
		GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red, FString::Printf(TEXT("You Hit : %s"), *HitResult->Actor->GetName()));

	}

    
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,TEXT("Action From Ray Casting"));
    
}

void AUnRealTutorialCharacter::createBulletHole(FHitResult* object)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Inside Create Bullet hole "));

	if (BulletHoleDecal != NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("BulletHoleDecal not null "));

		FVector BulletHoleSize = FVector(3.5f,7.0f,7.0f);
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHoleDecal, BulletHoleSize, object->ImpactPoint, object->ImpactNormal.Rotation(), 10.0f);

	}

}
