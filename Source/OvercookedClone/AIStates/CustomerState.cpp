// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStates/CustomerState.h"
#include "Net/UnrealNetwork.h"

void ACustomerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACustomerState, CurrentState);
}

void ACustomerState::SetCurrentState(ECustomerState NewState)
{
	CurrentState = NewState;
	OnCurrentStateChange.Broadcast(NewState);
}

ECustomerState ACustomerState::GetCurrentState() const
{
	return CurrentState;
}

