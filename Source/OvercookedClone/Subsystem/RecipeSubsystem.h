// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Recipe.h"
#include "RecipeSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API URecipeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	const class URecipeAsset* GetRecipeByType(ERecipeType RecipeType) const;

private:
	void LoadAllRecipes();

	UPROPERTY()
	TArray<TObjectPtr<class URecipeAsset>> LoadedRecipes;
	
	
};
