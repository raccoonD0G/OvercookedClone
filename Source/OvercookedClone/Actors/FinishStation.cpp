// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FinishStation.h"
#include "Actors/CustomerTable.h"
#include "Actors/Food.h"
#include "Interfaces/FinishStationInteractInterface.h"
#include "Actors/Ingredient.h"
#include "Subsystems/RecipeSubsystem.h"


AFinishStation::AFinishStation()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFinishStation::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnClicked.AddDynamic(this, &AFinishStation::OnActorClicked);

}


void AFinishStation::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	URecipeSubsystem* RecipeSubsystem = GetGameInstance()->GetSubsystem<URecipeSubsystem>();

	if (!RecipeSubsystem) return;

	TArray<FIngredientInfo> IngredientRequirements = RecipeSubsystem->GetRecipeByType(CurrentOrder.RecipeType)->RequiredIngredients;

	if (IngredientRequirements.Num() != Ingredients.Num())
	{
		Ingredients.Empty();
		return;
	}
	else
	{
		bool bIsCorrect = true;

		for (const auto& IngredientRequirement : IngredientRequirements)
		{
			if (!Ingredients.Contains(IngredientRequirement))
			{
				bIsCorrect = false;
			}
		}

		if (bIsCorrect)
		{
			AFood* NewFood = GetWorld()->SpawnActor<AFood>(FoodClasses[CurrentOrder.RecipeType]);
			CurrentOrder.CustomerTable->PlaceFood(NewFood);
		}
	}
}

void AFinishStation::Interact_Implementation(AActor* Caller)
{
	if (!Caller || !Caller->GetClass()->ImplementsInterface(UFinishStationInteractInterface::StaticClass()))
	{
		return;
	}

	AIngredient* Ingredient = IFinishStationInteractInterface::Execute_PutOutIngredient(Caller, this);

	if (!Ingredient) return;

	Ingredients.Add(FIngredientInfo(Ingredient->GetIngredientType(), Ingredient->GetIngredientState()));

	Ingredient->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Ingredient->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

}
