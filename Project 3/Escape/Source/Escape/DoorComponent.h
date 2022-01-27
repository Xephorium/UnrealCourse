// .

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorComponent.generated.h"

/*
 *  DoorComponent.h                                       Chris Cruzen
 *  Unreal Course                                           01.26.2022
 *
 *  Header file for DoorComponent.cpp.
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	float TargetAngle = 90.f;
	float AnimationLength = 1.3f;

private:
	float StartingYaw = 0.f;
	float CurrentYaw = 0.f;
	float TargetYaw = 0.f;

	float CurrentTime = 0.f;
	float EndTime = 0.f;

	bool RotationComplete = false; // For Optimization

public:	
	UDoorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

private:
	void ImmediatelyOpenDoor() const;
		
};
