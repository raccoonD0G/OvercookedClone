// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/KitchenGameState.h"


AKitchenGameState::AKitchenGameState()
{
	MouseCount = 0;
	bIsSeatsFull = false;
	Score = 100;
	
	MouseCountRatio = 0.1;
	SeatsFullRatio = 0.5;

	PrimaryActorTick.bCanEverTick = true;
}

void AKitchenGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Score -= MouseCount * MouseCountRatio * DeltaSeconds;

	if (bIsSeatsFull)
	{
		Score -= SeatsFullRatio * DeltaSeconds;
	}
}