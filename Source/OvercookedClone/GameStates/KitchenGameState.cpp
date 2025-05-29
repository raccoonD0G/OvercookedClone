// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/KitchenGameState.h"
#include "Net/UnrealNetwork.h"


AKitchenGameState::AKitchenGameState()
{
	MouseCount = 0;
	bIsSeatsFull = false;
	Score = 100;
	
	MouseCountRatio = 0.1;
	SeatsFullRatio = 0.5;

	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

void AKitchenGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKitchenGameState, MouseCount);
	DOREPLIFETIME(AKitchenGameState, bIsSeatsFull);
	DOREPLIFETIME(AKitchenGameState, Score);
}

void AKitchenGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		Score -= MouseCount * MouseCountRatio * DeltaSeconds;

		if (bIsSeatsFull)
		{
			Score -= SeatsFullRatio * DeltaSeconds;
		}
	}
}

void AKitchenGameState::IncreaseScore(float Amount)
{
	Score += Amount;
}

void AKitchenGameState::DecreaseScore(float Amount)
{
	Score -= Amount;
}
