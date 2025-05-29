// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Mouse.h"
#include "GameStates/KitchenGameState.h"
#include "Interfaces/DestroyMouseInterface.h"

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

	if (Caller && Caller->GetClass()->ImplementsInterface(UDestroyMouseInterface::StaticClass()))
	{
		IDestroyMouseInterface::Execute_DestroyMouse(Caller, this);
	}
}