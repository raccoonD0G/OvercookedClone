#pragma once

#include "CoreMinimal.h"
#include "Recipe.h"
#include "Order.generated.h"

USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	ERecipeType RecipeType;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class ACustomerTable> CustomerTable;

};