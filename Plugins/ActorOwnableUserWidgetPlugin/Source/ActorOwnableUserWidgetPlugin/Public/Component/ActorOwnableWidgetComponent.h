// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ActorOwnableWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (UI), meta = (BlueprintSpawnableComponent))
class ACTOROWNABLEUSERWIDGETPLUGIN_API UActorOwnableWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
