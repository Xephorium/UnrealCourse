#include "GrabberComponent.h"

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
}

