// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/RecipeSubsystem.h"
#include "Engine/DataTable.h"
#include "Recipe.h"

void URecipeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FStringAssetReference RecipeTablePath(TEXT("/Game/GameData/Recipes/DT_Recipes.DT_Recipes"));
    RecipeTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *RecipeTablePath.ToString()));

    if (RecipeTable)
    {
        LoadAllRecipes();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load RecipeTable at path: %s"), *RecipeTablePath.ToString());
    }
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

const FRecipeData& URecipeSubsystem::GetRecipeByType(ERecipeType RecipeType) const
{
    if (LoadedRecipes.Contains(RecipeType))
    {
        return *(LoadedRecipes.Find(RecipeType));
    }
    else
    {
        static FRecipeData DummyRecipe;
        return DummyRecipe;
    }
}
