// .

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorComponent.generated.h"

/*
 *  DoorComponent.h                                       Chris Cruzen
 *  Unreal Course                                           01.26.2022
 *
 *  Header file for DoorComponent.cpp.
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UDoorComponent : public UActorComponent {
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
	float TargetAngle = 90.f;
	UPROPERTY(EditAnywhere)
	float AnimationLength = 1.3f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;
	UPROPERTY(EditAnywhere)
	AActor *TriggeringActor;

private:
	float StartingYaw = 0.f;
	float CurrentYaw = 0.f;
	float TargetYaw = 0.f;

	float CurrentTime = 0.f;
	float EndTime = 0.f;

	bool RotationStarted = false;
	bool RotationComplete = true;

	bool IsDoorOpen = false;

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
	void OpenDoorImmediately() const;
	void RetrieveObjectReferences();
	void InitializeAnimationVariables();
	void OpenDoorWhenTriggered(float DeltaTime);
	void Extras() const;

};
