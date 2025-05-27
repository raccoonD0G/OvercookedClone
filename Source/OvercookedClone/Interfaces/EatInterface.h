// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "EatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable)
class UEatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OVERCOOKEDCLONE_API IEatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual void EndEating() = 0;
};
