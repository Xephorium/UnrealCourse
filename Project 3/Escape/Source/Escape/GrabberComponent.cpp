#include "Components/PrimitiveComponent.h"
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

	InitializeMemberClasses();
	BindInputActions();
}

void UGrabberComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update Player View
	UpdatePlayerView();

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

	// If Object Grabbed, Update Location
	if (PhysicsHandleComponent->GrabbedComponent) {
		PhysicsHandleComponent->SetTargetLocation(RaycastEndPoint);
	}
}


/*--- Private Functions ---*/

void UGrabberComponent::InitializeMemberClasses() {

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
}

void UGrabberComponent::BindInputActions() {
	if (InputComponent) {
		InputComponent->BindAction(
			TEXT("Grab"), 
			EInputEvent::IE_Pressed,
			this, // A new keyword! Returns a pointer to the calling object.
			&UGrabberComponent::GrabObject // Note: no parenthesis!
		);
		InputComponent->BindAction(
			TEXT("Grab"), 
			EInputEvent::IE_Released,
			this,
			&UGrabberComponent::ReleaseObject
		);
	}
}

void UGrabberComponent::UpdatePlayerView() {

	// Update Player Location/Rotation
	PlayerLocation = FVector();
	FRotator PlayerRotation = FRotator();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotation
	);

	// Update Raycast End Point 
	RaycastEndPoint = PlayerLocation + PlayerRotation.Vector() * PlayerReach;
}

AActor *UGrabberComponent::GetActorInView() {

	// Initialize Raycast Variavbles
	FHitResult RaycastHit;
	FCollisionQueryParams RaycastParams = FCollisionQueryParams(
		FName(TEXT("")), // ???
		false, // Whether to use Visibility Collision
		GetOwner()// Any Actor to ignore? (Player!)
	);

	// Perform Raycast
	GetWorld()->LineTraceSingleByObjectType(
		OUT RaycastHit,
		PlayerLocation,
		RaycastEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		RaycastParams
	);

	return RaycastHit.GetActor();
}

void UGrabberComponent::GrabObject() {
	AActor * RaycastHitActor = GetActorInView();

	// If Actor Found, Grab
	if (RaycastHitActor) {
		PhysicsHandleComponent->GrabComponentAtLocation(
			Cast<UPrimitiveComponent>(
				RaycastHitActor->GetComponentByClass(UPrimitiveComponent::StaticClass())
			),
			NAME_None,
			RaycastHitActor->GetActorLocation()
		);
	}
}

void UGrabberComponent::ReleaseObject() {
	PhysicsHandleComponent->ReleaseComponent();
}