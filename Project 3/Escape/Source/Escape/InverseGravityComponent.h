// .

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InverseGravityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UInverseGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector GravityDirection = FVector(0, 978.f, 0);

public:	
	// Sets default values for this component's properties
	UInverseGravityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
