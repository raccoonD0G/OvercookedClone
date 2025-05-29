// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStates/PlayerCharacterState.h"
#include "Net/UnrealNetwork.h"

APlayerCharacterState::APlayerCharacterState()
{
	bReplicates = true;
}

void APlayerCharacterState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerCharacterState, CurrentState);
}

void APlayerCharacterState::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetCurrentState(GetCurrentState());
}

void APlayerCharacterState::SetCurrentState(EPlayerCharacterState NewState)
{
	Server_SetCurrentState(NewState);
}

void APlayerCharacterState::Server_SetCurrentState_Implementation(EPlayerCharacterState NewState)
{
	CurrentState = NewState;
	switch (CurrentState)
	{
	case EPlayerCharacterState::TakeOrder:
		break;
	case EPlayerCharacterState::TakeIngredient:
		break;
	case EPlayerCharacterState::ChangeIngredientState:
		break;
	case EPlayerCharacterState::PutOnFinishTable:
		break;
	}
}
