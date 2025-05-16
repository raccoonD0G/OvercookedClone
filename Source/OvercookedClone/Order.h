#pragma once

#include "CoreMinimal.h"
#include "Recipe.h"
#include "Order.generated.h"

USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_BODY()
	
public:
	ERecipeType RecipeType;

	UPROPERTY()
	TObjectPtr<class ACustomerTable> CustomerTable;

};