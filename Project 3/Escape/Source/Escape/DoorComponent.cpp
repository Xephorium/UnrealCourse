
#include "DoorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

/*
 *  DoorComponent.cpp                                Chris Cruzen
 *  Unreal Course                                      01.26.2022
 *
 *    DoorComponent animates the smooth rotation of a door across
 *  a variable number of degrees in a variable amount of time.
 */


/*--- Lifecycle Functions ---*/

UDoorComponent::UDoorComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorComponent::BeginPlay() {
	Super::BeginPlay();

	// Implementation #1
	//OpenDoorImmediately();

	// Implementation #2
	RetrieveObjectReferences();
}

void UDoorComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Implementation #2
	OpenDoorWhenTriggered(DeltaTime);
}


/*--- Private Functions ---*/

// Note: This function contains implementation #1. Opens door immediately
//       when called, with no animation.
void UDoorComponent::OpenDoorImmediately() const {
	float FinalRotation = 90.f;

	// Get Current Actor Rotation
	// Note: Parameter order is Pitch (Y), Roll (X), Yaw (Z) instead of the
	//       universal coordinate standard XYZ because Unreal Engine was
	//       programmed by baboons.
	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	// Calculate New Actor Rotation
	FRotator NewRotation = FRotator(
		CurrentRotation.Pitch,
		CurrentRotation.Roll + FinalRotation,
		CurrentRotation.Yaw
	);

	// Rotate Actor
	GetOwner()->SetActorRotation(NewRotation);
}

// Note: This function retrieves and null checks the unreal
//       objects needed for implementation #2.
void UDoorComponent::RetrieveObjectReferences() {
	
	// Get Player Pawn
	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Perform Initialization Null Checks
	if (!PressurePlate) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s has DoorComponent, but no PressurePlate set."),
			*GetOwner()->GetName()
		);
	}
}

// Note: This function initializes the values needed for implementation #2.
void UDoorComponent::InitializeAnimationVariables() {

	// Initialize Rotation Values
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = StartingYaw;
	if (IsDoorOpen) {
		TargetYaw = CurrentYaw - TargetAngle;
	} else {
		TargetYaw = CurrentYaw + TargetAngle;
	}

	// Initialize Time Values
	EndTime = AnimationLength;
}

// Note: This function contains implementation #2. Animates the smooth
//       opening of our door when activated by the PressurePlate trigger
//       volume.
void UDoorComponent::OpenDoorWhenTriggered(float DeltaTime) {

	// Perform Passive Null Check
	if (!PressurePlate) {
		return;
	}

	// Check for Trigger Volume Activation
	if (PressurePlate->IsOverlappingActor(TriggeringActor) && !RotationStarted) {
		RotationStarted = true;
	}

	// Handle Door Animation
	if (RotationStarted) {

		// Reset Animation Start Time
		if (RotationComplete) {
			CurrentTime = 0.f;
			RotationComplete = false;
			InitializeAnimationVariables();
		}

		// Update Current Time
		CurrentTime += DeltaTime;

		// Check if Animation Active
		if (!RotationComplete) {

			// Check if Animating
			if (CurrentTime < EndTime) {

				// Calculate Completion Percentage
				float CurrentPercent = CurrentTime / EndTime;

				// Update Rotation
				CurrentYaw = FMath::InterpEaseInOut(StartingYaw, TargetYaw, CurrentPercent, 2.f);
				GetOwner()->SetActorRotation(FRotator(
					GetOwner()->GetActorRotation().Pitch,
					CurrentYaw,
					GetOwner()->GetActorRotation().Roll
				));

			} else {

				// Set Final Rotation
				GetOwner()->SetActorRotation(FRotator(
					GetOwner()->GetActorRotation().Pitch,
					TargetYaw,
					GetOwner()->GetActorRotation().Roll
				));
				RotationStarted = false;
				RotationComplete = true;
				IsDoorOpen = !IsDoorOpen;
			}
		}
	}
}

// Note: This function contains extras! Cool info covered in the slides that I'd
//       like to record without working into my solution.
void UDoorComponent::Extras() const {

	// Returns time since the beginning of play!
	// Can be used to make timers.
	GetWorld()->GetTimeSeconds();
}