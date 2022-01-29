#include "DrawDebugHelpers.h"
#include "GrabberComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

/*
 *  GrabberComponent.cpp                               Chris Cruzen
 *  Unreal Course                                        01.29.2022
 *
 *    GrabberComponent gives its actor the ability to grab and move
 *  other objects in the scene.
 */


/*--- Macros ---*/

// Note: This is how we define a macro! In this case, it doesn't actually
//       do anything. But that's okay because we just want the added
//       readability. 
#define OUT


/*--- Lifecycle Functions ---*/

UGrabberComponent::UGrabberComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabberComponent::BeginPlay() {
	Super::BeginPlay();
	
}

void UGrabberComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Player Location/Rotation
	FVector PlayerLocation = FVector();
	FRotator PlayerRotation = FRotator();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("Player Location: %s"), *PlayerLocation.ToString());

	// Draw Raycast
	FVector RaycastEndPoint = PlayerLocation + PlayerRotation.Vector() * PlayerReach;
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		RaycastEndPoint,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		0.5f
	);

	// Identify object in view (and whether we can interact)
}

