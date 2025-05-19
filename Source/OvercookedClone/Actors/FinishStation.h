// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Order.h"
#include "Recipe.h"
#include "Interfaces/InteractableInterface.h"
#include "FinishStation.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API AFinishStation : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AFinishStation();

protected:
	virtual void PostInitializeComponents() override;
	
public:
	UFUNCTION()
	void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);

	FORCEINLINE void SetCurrentOrder(FOrder NewOrder) { CurrentOrder = NewOrder; }

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TSet<FIngredientInfo> Ingredients;

	FOrder CurrentOrder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "ture"))
	TMap<ERecipeType, TSubclassOf<class AFood>> FoodClasses;

public:
	virtual void Interact_Implementation(AActor* Caller);
};
