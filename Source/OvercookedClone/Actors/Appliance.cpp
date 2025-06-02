// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Appliance.h"
#include "Interfaces/ChangeIngredientStateInterface.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ActorOwnableWidgetComponent.h"
#include "Widget/FloatingMessageWidget.h"

AAppliance::AAppliance()
{
	PrimaryActorTick.bCanEverTick = true;

	StateChangeWidgetComponent = CreateDefaultSubobject<UActorOwnableWidgetComponent>(TEXT("StateChangeWidgetComponent"));
	StateChangeWidgetComponent->SetupAttachment(RootComponent);
}


void AAppliance::Interact(AActor* Caller)
{
	Super::Interact(Caller);
	if (Caller && Caller->GetClass()->ImplementsInterface(UChangeIngredientStateInterface::StaticClass()))
	{
		EIngredientState State = IChangeIngredientStateInterface::Execute_GetIngredientStateOnHand(Caller);
		if (State == EIngredientState::Raw)
		{
			StartStateChangeWidget();
			IChangeIngredientStateInterface::Execute_ChangeIngredientState(Caller, OutIngredientState);
		}
	}
}

void AAppliance::StartStateChangeWidget()
{
	UFloatingMessageWidget* FloatingMessageWidget = Cast<UFloatingMessageWidget>(StateChangeWidgetComponent->GetWidget());
	if (FloatingMessageWidget)
	{
		FloatingMessageWidget->Start();
	}
}
