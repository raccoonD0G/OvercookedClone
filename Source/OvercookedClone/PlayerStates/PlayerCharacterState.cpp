// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStates/PlayerCharacterState.h"
#include "Net/UnrealNetwork.h"
#include "Characters/PlayerCharacter.h"
#include "Actors/FinishStation.h"
#include "GameFramework/GameState.h"

APlayerCharacterState::APlayerCharacterState()
{
	bReplicates = true;
}

void APlayerCharacterState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerCharacterState, NextTask);
}

void APlayerCharacterState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetNextTask(EPlayerTask::TakeOrder);
}

void APlayerCharacterState::SetNextTask(EPlayerTask NewTask)
{
	Server_SetNextTask(NewTask);
}

void APlayerCharacterState::OnRep_NextTask()
{
	OnNextTaskChange.Broadcast(NextTask);
}

void APlayerCharacterState::Server_SetNextTask_Implementation(EPlayerTask NewTask)
{
	OnNextTaskChange.Broadcast(NewTask);

	NextTask = NewTask;
}

void APlayerCharacterState::Server_EndTakeOrder_Implementation()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState)
	{
		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			if (APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(PlayerState))
			{
				PlayerCharacterState->SetNextTask(EPlayerTask::TakeIngredient);
			}
		}
	}
}

void APlayerCharacterState::Server_EndClickFinishStation_Implementation()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState)
	{
		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			if (APlayerCharacterState* PlayerCharacterState = Cast<APlayerCharacterState>(PlayerState))
			{
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
				const FOrder& Order = PlayerCharacter->GetFinishStation()->GetCurrentOrder();

				if (Order.RecipeType == ERecipeType::None)
				{
					PlayerCharacterState->SetNextTask(EPlayerTask::TakeOrder);
				}
				else
				{
					PlayerCharacterState->SetNextTask(EPlayerTask::TakeIngredient);
				}
			}
		}
	}
}

void APlayerCharacterState::EndTakeOrder()
{
	SetNextTask(EPlayerTask::TakeIngredient);
	Server_EndTakeOrder();
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

	Server_EndClickFinishStation();
}

