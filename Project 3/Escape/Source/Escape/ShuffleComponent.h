
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShuffleComponent.generated.h"

/*
 *  ShuffleComponent.h                                    Chris Cruzen
 *  Unreal Course                                           01.25.2022
 *
 *  Header file for ShuffleComponent.cpp
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UShuffleComponent : public UActorComponent {
	GENERATED_BODY()

private:
	float ShuffleSpeed = 0.5; 
	float ShuffleDirection = 1.0;

public:	
	UShuffleComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction*
		ThisTickFunction
	) override;
		
};
