#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"

/*
 *  GrabberComponent.h                                    Chris Cruzen
 *  Unreal Course                                           01.29.2022
 *
 *  Header file for GrabberComponent.cpp.
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabberComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float PlayerReach = 200.f;

private:
    // Note: nullptr initializes a pointer to help prevent a crash.
	//       Best to use when declaring member pointers for a class
	//       that may or may not exist depending on lifecycle. In
	//       this case, the component may be attached by Unreal later
	//       than we try to reference it.
	UPhysicsHandleComponent *PhysicsHandleComponent = nullptr;
	UInputComponent *InputComponent = nullptr;

public:	
	UGrabberComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;
		
private:
	void GrabObject();
};
