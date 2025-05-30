// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Appliance.h"
#include "Interfaces/ChangeIngredientStateInterface.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"

AAppliance::AAppliance()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AAppliance::Interact(AActor* Caller)
{
	Super::Interact(Caller);
	if (Caller && Caller->GetClass()->ImplementsInterface(UChangeIngredientStateInterface::StaticClass()))
	{
		IChangeIngredientStateInterface::Execute_ChangeIngredientState(Caller, OutIngredientState);
	}
}
