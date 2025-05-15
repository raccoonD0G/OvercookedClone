// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableBase.generated.h"

UCLASS(Blueprintable, BlueprintType)
class OVERCOOKEDCLONE_API AInteractableBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
	AInteractableBase();
};
