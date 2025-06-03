// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Order.h"
#include "Recipe.h"
#include "Actors/InteractableBase.h"
#include "FinishStation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIngredientInfosChangeDelegate, const TArray<FIngredientInfo>&, IngredientInfos);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrderSetDelegate, const FOrder&, NewOrder);

UCLASS()
class OVERCOOKEDCLONE_API AFinishStation : public AInteractableBase
{
	GENERATED_BODY()
	
public:	
	AFinishStation();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void OnClicked();

	UFUNCTION(BlueprintCallable)
	void SetCurrentOrder(FOrder NewOrder);

	UFUNCTION(BlueprintCallable)
	const FOrder& GetCurrentOrder() const { return CurrentOrder; }

	FOnIngredientInfosChangeDelegate OnIngredientInfosChange;
	FOnOrderSetDelegate OnOrderSet;

	UFUNCTION(BlueprintCallable)
	void AddIngredientInfo(FIngredientInfo IngredientInfo);

protected:
	virtual void Interact(AActor* Caller) override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Ingredients, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<FIngredientInfo> IngredientInfos;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentOrder, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FOrder CurrentOrder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "ture"))
	TMap<ERecipeType, TSubclassOf<class AFood>> FoodClasses;

private:
	UFUNCTION()
	void OnRep_CurrentOrder();

	UFUNCTION()
	void OnRep_Ingredients();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> MeshComponent;
};
