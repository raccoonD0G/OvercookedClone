// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIState/AIState.h"
#include "CustomerState.generated.h"

UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	None,
	MoveToRegister,
	MoveToTable,
	Eating,
	Exiting
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentStateChangeDelegate, ECustomerState, NewState);

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API ACustomerState : public AAIState
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	ECustomerState CurrentState;

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentState(ECustomerState NewState);

	FOnCurrentStateChangeDelegate OnCurrentStateChange;
	
};
