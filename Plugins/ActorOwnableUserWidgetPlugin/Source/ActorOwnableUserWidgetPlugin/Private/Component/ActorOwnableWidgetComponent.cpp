// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActorOwnableWidgetComponent.h"
#include "Widget/ActorOwnableUserWidget.h"

void UActorOwnableWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UActorOwnableUserWidget* ActorOwnableUserWidget = Cast<UActorOwnableUserWidget>(GetWidget());
	if (ActorOwnableUserWidget)
	{
		ActorOwnableUserWidget->SetOwningActor(GetOwner());
	}
}
