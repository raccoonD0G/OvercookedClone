// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Mouse.h"
#include "GameStates/KitchenGameState.h"

AMouse::AMouse()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMouse::BeginPlay()
{
	Super::BeginPlay();

	AKitchenGameState* KitchenGameState = GetWorld()->GetGameState<AKitchenGameState>();
	if (KitchenGameState)
	{
		KitchenGameState->IncreaseMouseCount();
	}
}

void AMouse::Interact(AActor* Caller)
{
	Super::Interact(Caller);

	AKitchenGameState* KitchenGameState = GetWorld()->GetGameState<AKitchenGameState>();
	if (KitchenGameState)
	{
		KitchenGameState->DecreaseMouseCount();
	}

	GetWorld()->DestroyActor(this);
}