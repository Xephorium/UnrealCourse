
#include "ShuffleComponent.h"
#include "GameFramework/Actor.h"

/*
 *  ShuffleComponent.cpp                                  Chris Cruzen
 *  Unreal Course                                           01.25.2022
 *
 *    ShuffleComponent is the first C++ component I've built on my own
 *  in Unreal Engine! It simply moves the actor it's attached to
 *  diagonally across the game space. This is mostly to establish
 *  my own cody style preferences and practice what I learned in 
 *  the course lesson that covered WorldPosition.cpp. 
 */


/*--- Constructor ---*/

UShuffleComponent::UShuffleComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}


/*--- Lifecycle Methods ---*/

void UShuffleComponent::BeginPlay() {
	Super::BeginPlay();
}

/*  Note: Moves the owning actor diagonally across the map. Movement is
 *  linked to framerate, which is terrible. But idk how to access delta
 *  time yet so whatever.
 */
void UShuffleComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Actor's Current Location
	FVector ActorLocation = GetOwner()->GetActorLocation();

	// Calculate Actor's Next Location
	FVector NewActorLocation = {
		ActorLocation.X + (ShuffleSpeed * ShuffleDirection),
		ActorLocation.Y - ShuffleSpeed * ShuffleDirection,
		ActorLocation.Z
	};
	
	// Update Actor's Location
	if(!GetOwner()->SetActorLocation(NewActorLocation, true)) {

		// Reverse Direction if Collision Encountered
		ShuffleDirection *= -1;
	}
}

