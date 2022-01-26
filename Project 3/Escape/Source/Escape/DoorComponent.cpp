
#include "DoorComponent.h"
#include "GameFramework/Actor.h"

/*
 *  DoorComponent.cpp                                     Chris Cruzen
 *  Unreal Course                                           01.26.2022
 *
 *    DoorComponent rotates the door it's attached to! 
 */


/*--- Constructor ---*/

UDoorComponent::UDoorComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}


/*--- Lifecycle Methods ---*/

void UDoorComponent::BeginPlay() {
	Super::BeginPlay();

	float FinalRotation = 90.f;

	FRotator CurrentRotation = GetOwner()->GetActorRotation(); // Format: Y, X, X (??? I hate this)
	FRotator NewRotation = FRotator(
		CurrentRotation.Pitch,
		CurrentRotation.Roll + FinalRotation,
		CurrentRotation.Yaw
	);
	GetOwner()->SetActorRotation(NewRotation);
}

void UDoorComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

