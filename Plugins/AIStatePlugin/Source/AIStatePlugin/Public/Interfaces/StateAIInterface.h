// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "StateAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable)
class UStateAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AISTATEPLUGIN_API IStateAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual class AAIState* GetAIState() const = 0;

	UFUNCTION(BlueprintCallable)
	virtual void SetAIState(class AAIState* NewAIState) = 0;
	
};
