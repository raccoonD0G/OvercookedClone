// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStates/WaiterState.h"
#include "Net/UnrealNetwork.h"


void AWaiterState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWaiterState, CurrentState);
}

void AWaiterState::SetCurrentState(EWaiterState NewState)
{
	CurrentState = NewState;
	OnCurrentStateChange.Broadcast(NewState);
}

EWaiterState AWaiterState::GetCurrentState() const
{
	return CurrentState;
}