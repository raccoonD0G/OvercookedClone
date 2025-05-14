// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Recipe.h"
#include "RecipeAsset.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API URecipeAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
    FRecipeData Recipe;

    /** 식별자 등록 (Primary Asset Label 등) */
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId("Recipe", GetFName());
    }
};
