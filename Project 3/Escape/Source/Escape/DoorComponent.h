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
	// Sets default values for this component's properties
	UDoorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

		
};
