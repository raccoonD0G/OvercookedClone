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

    const FRecipeData* GetRecipeByType(ERecipeType RecipeType) const;

private:
    void LoadAllRecipes();

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UDataTable> RecipeTable;

    // Ä³½Ã
    TMap<ERecipeType, FRecipeData> LoadedRecipes;
	
	
};
