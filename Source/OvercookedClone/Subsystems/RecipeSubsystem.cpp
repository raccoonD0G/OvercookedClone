// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/RecipeSubsystem.h"
#include "Engine/DataTable.h"
#include "Recipe.h"

void URecipeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    LoadAllRecipes();
}

void URecipeSubsystem::LoadAllRecipes()
{
    if (!RecipeTable) return;

    static const FString Context(TEXT("RecipeSubsystem"));
    TArray<FRecipeData*> Rows;
    RecipeTable->GetAllRows<FRecipeData>(Context, Rows);

    for (FRecipeData* Row : Rows)
    {
        if (Row)
        {
            LoadedRecipes.Add(Row->RecipeType, *Row);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[RecipeSubsystem] Loaded %d recipes"), LoadedRecipes.Num());
}

const FRecipeData* URecipeSubsystem::GetRecipeByType(ERecipeType RecipeType) const
{
    return LoadedRecipes.Find(RecipeType);
}
