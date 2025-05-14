// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RecipeSubsystem.h"
#include "GameData/RecipeAsset.h"
#include "Engine/AssetManager.h"

void URecipeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    LoadAllRecipes();
}

void URecipeSubsystem::LoadAllRecipes()
{
    TArray<FPrimaryAssetId> RecipeAssetIds;
    UAssetManager::Get().GetPrimaryAssetIdList(FPrimaryAssetType("Recipe"), RecipeAssetIds);

    for (const FPrimaryAssetId& Id : RecipeAssetIds)
    {
        FSoftObjectPath AssetPath = UAssetManager::Get().GetPrimaryAssetPath(Id);
        URecipeAsset* Recipe = Cast<URecipeAsset>(AssetPath.TryLoad());
        if (Recipe)
        {
            LoadedRecipes.Add(Recipe);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("[RecipeSubsystem] Loaded %d recipes"), LoadedRecipes.Num());
}

const URecipeAsset* URecipeSubsystem::GetRecipeByType(ERecipeType RecipeType) const
{
    for (const URecipeAsset* Recipe : LoadedRecipes)
    {
        if (Recipe && Recipe->Recipe.RecipeType == RecipeType)
        {
            return Recipe;
        }
    }
    return nullptr;
}
