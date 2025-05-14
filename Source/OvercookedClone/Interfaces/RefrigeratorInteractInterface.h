// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Recipe.h"
#include "RefrigeratorInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class URefrigeratorInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OVERCOOKEDCLONE_API IRefrigeratorInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ObtainIngredients(AActor* Caller, class AIngredient* SelectedIngredient);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	const TArray<EIngredientType> GetNecessaryIngredients();
};
