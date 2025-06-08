// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIStates/AIState.h"
#include "WaiterState.generated.h"

UENUM(BlueprintType)
enum class EWaiterState : uint8
{
	None,
	MoveToRandomPos,
	WaitForNextMove,
	MoveToFinishStation,
	MoveToTable,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaiterStateChangeDelegate, EWaiterState, NewState);

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AWaiterState : public AAIState
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EWaiterState NewState);

	UFUNCTION(BlueprintCallable)
	EWaiterState GetCurrentState() const;

	FOnWaiterStateChangeDelegate OnCurrentStateChange;

private:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWaiterState CurrentState;
	
	
};
