// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableBase.h"
#include "Recipe.h"
#include "Refrigerator.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ARefrigerator : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	ARefrigerator();

public:
	virtual void Interact_Implementation(AActor* Caller) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EIngredientType, TSubclassOf<class AIngredient>> IngredientClasses;
	
};
