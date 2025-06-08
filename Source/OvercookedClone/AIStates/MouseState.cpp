// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStates/MouseState.h"
#include "Net/UnrealNetwork.h"

void AMouseState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMouseState, CurrentState);
}

void AMouseState::SetCurrentState(EMouseState NewState)
{
	CurrentState = NewState;
	OnCurrentStateChange.Broadcast(NewState);
}

EMouseState AMouseState::GetCurrentState() const
{
	return CurrentState;
}
