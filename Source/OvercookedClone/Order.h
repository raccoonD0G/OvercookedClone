#pragma once

#include "CoreMinimal.h"
#include "Recipe.h"
#include "Order.generated.h"

USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERecipeType RecipeType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class ACustomerTable> CustomerTable;

};