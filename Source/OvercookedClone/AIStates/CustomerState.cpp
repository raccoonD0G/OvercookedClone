// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStates/CustomerState.h"

void ACustomerState::SetCurrentState(ECustomerState NewState)
{
	CurrentState = NewState;
	OnCurrentStateChange.Broadcast(NewState);
}
