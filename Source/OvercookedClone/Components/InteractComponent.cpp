// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractComponent.h"
#include "Components/ActorOwnableWidgetComponent.h"
#include "Components/BoxComponent.h"

UInteractComponent::UInteractComponent()
{
	SetIsReplicatedByDefault(true);
	SetCollisionProfileName(TEXT("InteractObject"));
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractComponent::Interact(AActor* Caller)
{
	OnInteract.Broadcast(Caller);
}

void UInteractComponent::ShowInteractWidget()
{
	if (ActorOwnableWidgetComponent)
	{
		ActorOwnableWidgetComponent->SetVisibility(true, true);
		ActorOwnableWidgetComponent->SetHiddenInGame(false);
		ActorOwnableWidgetComponent->SetComponentTickEnabled(true);
	}
}

void UInteractComponent::CloseInteractWidget()
{
	if (ActorOwnableWidgetComponent)
	{
		ActorOwnableWidgetComponent->SetVisibility(false, true);
		ActorOwnableWidgetComponent->SetHiddenInGame(true);
		ActorOwnableWidgetComponent->SetComponentTickEnabled(false);
	}
}