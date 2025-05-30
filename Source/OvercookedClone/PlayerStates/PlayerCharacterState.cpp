// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStates/PlayerCharacterState.h"
#include "Net/UnrealNetwork.h"
#include "Characters/PlayerCharacter.h"
#include "Actors/FinishStation.h"

APlayerCharacterState::APlayerCharacterState()
{
	bReplicates = true;
}

void APlayerCharacterState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerCharacterState, NextTask);
}

void APlayerCharacterState::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetNextTask(GetCurrentState());
}

void APlayerCharacterState::SetNextTask(EPlayerTask NewTask)
{
	Server_SetNextTask(NewTask);
}

void APlayerCharacterState::Server_SetNextTask_Implementation(EPlayerTask NewTask)
{
	switch (NewTask)
	{
	case EPlayerTask::TakeOrder:
		break;
	case EPlayerTask::TakeIngredient:
		break;
	case EPlayerTask::ChangeIngredientStateOrPutOnFinishTable:
		break;
	case EPlayerTask::PutOnFinishTable:
		break;
	}

	OnNextTaskChange.Broadcast(NewTask);

	NextTask = NewTask;
}

void APlayerCharacterState::EndTakeOrder()
{
	SetNextTask(EPlayerTask::TakeIngredient);
}

void APlayerCharacterState::EndTakeIngredient()
{
	SetNextTask(EPlayerTask::ChangeIngredientStateOrPutOnFinishTable);
}

void APlayerCharacterState::EndChangeIngredientState()
{
	SetNextTask(EPlayerTask::PutOnFinishTable);
}

void APlayerCharacterState::EndPutOnFinishTable()
{
	SetNextTask(EPlayerTask::TakeIngredient);
}

void APlayerCharacterState::EndClickFinishStation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	const FOrder& Order = PlayerCharacter->GetFinishStation()->GetCurrentOrder();

	if (Order.RecipeType == ERecipeType::None)
	{
		SetNextTask(EPlayerTask::TakeOrder);
	}
	else
	{
		SetNextTask(EPlayerTask::TakeIngredient);
	}
}

