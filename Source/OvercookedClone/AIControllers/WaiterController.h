// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllers/StateAIController.h"
#include "AIStates/WaiterState.h"
#include "WaiterController.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AWaiterController : public AStateAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnCurrentStateChange(EWaiterState NewState);

	
	
};
