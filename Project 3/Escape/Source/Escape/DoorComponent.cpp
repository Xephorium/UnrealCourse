
#include "DoorComponent.h"
#include "GameFramework/Actor.h"

/*
 *  DoorComponent.cpp                                Chris Cruzen
 *  Unreal Course                                      01.26.2022
 *
 *    DoorComponent animates the smooth rotation of a door across
 *  a variable number of degrees in a variable amount of time.
 */


/*--- Constructor ---*/

UDoorComponent::UDoorComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}


/*--- Lifecycle Functions ---*/

void UDoorComponent::BeginPlay() {
	Super::BeginPlay();

	// Implementation #1 (Contained entirely in below method)
	//ImmediatelyOpenDoor();

	// Implementation #2 (The rest of the custom code in this class)

	// Initialize Rotation Values
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = StartingYaw;
	TargetYaw = CurrentYaw + TargetAngle;

	// Initialize Time Values
	EndTime = AnimationLength;
}

void UDoorComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
			RotationComplete = true;
		}
	}
}


/*--- Private Functions ---*/

void UDoorComponent::ImmediatelyOpenDoor() const {
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