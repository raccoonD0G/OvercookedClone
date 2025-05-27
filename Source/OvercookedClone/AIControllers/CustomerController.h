// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/StateAIController.h"
#include "AIStates/CustomerState.h"
#include "CustomerController.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API ACustomerController : public AStateAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnCurrentStateChange(ECustomerState NewState);
	
	
};
