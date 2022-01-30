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

	// Search Owning Actor for a Specific Component Type (Returns first found!)
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// Null Check PhysicsHandleComponent
	if (!PhysicsHandleComponent) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("No PhysicsHandleComponent found on Actor %s"),
			*GetOwner()->GetName()
		);
	}

	// Bind Input Actions
	InputComponent->BindAction(
		TEXT("Grab"), 
		EInputEvent::IE_Pressed,
		this, // A new keyword! Returns a pointer to the calling object.
		&UGrabberComponent::GrabObject // Note: no parenthesis!
	);
	
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

	// Calculate Raycast End Point 
	FVector RaycastEndPoint = PlayerLocation + PlayerRotation.Vector() * PlayerReach;

	// Draw Debug Raycast
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

	// Perform Raycast
	FHitResult RaycastHit;
	FCollisionQueryParams RaycastParams = FCollisionQueryParams(
		FName(TEXT("")), // ???
		false, // Whether to use Visibility Collision
		GetOwner()// Any Actor to ignore? (Player!)
	);
	GetWorld()->LineTraceSingleByObjectType(
		OUT RaycastHit,
		PlayerLocation,
		RaycastEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		RaycastParams
	);

	// Log Raycast Hit Actor
	AActor *RaycastHitActor = RaycastHit.GetActor();
	if (RaycastHitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Detected Actor: %s"), *RaycastHitActor->GetName());
	}

	// Identify object in view (and whether we can interact)
}


/*--- Private Functions ---*/

void UGrabberComponent::GrabObject() {
	UE_LOG(LogTemp, Error, TEXT("This is a test!"));
}