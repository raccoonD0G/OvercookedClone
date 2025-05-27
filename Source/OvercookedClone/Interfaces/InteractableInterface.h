// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */

class OVERCOOKEDCLONE_API IInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact(AActor* Caller) = 0;
};
