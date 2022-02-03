#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

/*
 *  BasePawn.h                                            Chris Cruzen
 *  Unreal Course                                           02.03.2022
 *
 *  Header file for BasePawn.cpp.
 */

UCLASS()
class TOONTANKS_API ABasePawn : public APawn {
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
