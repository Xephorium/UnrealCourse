#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

/*
 *  BasePawn.cpp                                      Chris Cruzen
 *  Unreal Course                                       02.03.2022
 *
 *    BasePawn contains the basic pawn functionality that we'll be
 *  including in our Tank and Turret classes.
 */


/*--- Lifecycle Functions ---*/

ABasePawn::ABasePawn() {
	PrimaryActorTick.bCanEverTick = true;

	// Create New Capsule Component!
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));

	// Assign New Capsule Component to Root
	RootComponent = CapsuleComponent;
}

void ABasePawn::BeginPlay() {
	Super::BeginPlay();
}

void ABasePawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Note: New Pawn function! Called to bind functionality to input.
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

