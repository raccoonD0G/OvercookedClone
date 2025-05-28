// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Order.h"
#include "Recipe.h"
#include "KitchenWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API UKitchenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetRecipeText(const FText& InText);

	void AddIngredientText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	void Init(class AFinishStation* TargetFinishStation);

	UFUNCTION()
	void ResetIngredients(const TArray<FIngredientInfo>& IngredientInfos);

	UFUNCTION()
	void SetOrder(const FOrder& NewOrder);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Recipe;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> Ingredients;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFinishStation> FinishStation;
	
};
