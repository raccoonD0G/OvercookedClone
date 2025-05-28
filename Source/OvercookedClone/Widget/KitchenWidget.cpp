// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/KitchenWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Actors/FinishStation.h"
#include "Actors/Ingredient.h"

void UKitchenWidget::SetRecipeText(const FText& InText)
{
	if (Recipe)
	{
		Recipe->SetText(InText);
	}
}

void UKitchenWidget::AddIngredientText(const FText& InText)
{
	// 텍스트 블록 생성
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(this);
	if (NewTextBlock)
	{
		NewTextBlock->SetText(InText);

		// VerticalBox에 추가
		UVerticalBoxSlot* NewSlot = Ingredients->AddChildToVerticalBox(NewTextBlock);
		if (NewSlot)
		{
			NewSlot->SetPadding(FMargin(5.f));
			NewSlot->SetHorizontalAlignment(HAlign_Left);
		}
	}
}

void UKitchenWidget::ResetIngredients(const TArray<FIngredientInfo>& IngredientInfos)
{
	Ingredients->ClearChildren();

	const UEnum* EnumPtr = StaticEnum<EIngredientType>();

	for (const auto& IngredientInfo : IngredientInfos)
	{
		FText IngredientText = EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(IngredientInfo.Ingredient));
		AddIngredientText(IngredientText);
	}
}

void UKitchenWidget::SetOrder(const FOrder& NewOrder)
{
	const UEnum* EnumPtr = StaticEnum<ERecipeType>();
	FText RecipeText = EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(NewOrder.RecipeType));
	SetRecipeText(RecipeText);
}

void UKitchenWidget::Init(AFinishStation* TargetFinishStation)
{
	FinishStation = TargetFinishStation;
	FinishStation->OnIngredientInfosChange.AddDynamic(this, &UKitchenWidget::ResetIngredients);
	FinishStation->OnOrderSet.AddDynamic(this, &UKitchenWidget::SetOrder);
}
