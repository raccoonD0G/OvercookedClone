// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIStates/AIState.h"
#include "CustomerState.generated.h"

UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	None,
	MoveToRegister,
	MoveToTable,
	WaitForFood,
	Eating,
	Exiting
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomerStateChangeDelegate, ECustomerState, NewState);

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API ACustomerState : public AAIState
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentState(ECustomerState NewState);

	UFUNCTION(BlueprintCallable)
	ECustomerState GetCurrentState() const;

	FOnCustomerStateChangeDelegate OnCurrentStateChange;

private:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECustomerState CurrentState;
};
