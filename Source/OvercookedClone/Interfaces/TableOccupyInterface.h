// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "TableOccupyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable)
class UTableOccupyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OVERCOOKEDCLONE_API ITableOccupyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual void OccupyTable(class ACustomerTable* Table) = 0;

	UFUNCTION(BlueprintCallable)
	virtual class ACustomerTable* OccupiedTable() const = 0;
};
