// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Recipe.h"
#include "CustomerTable.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACustomerTable : public AActor
{
	GENERATED_BODY()
	
public:	
	ACustomerTable();
	
public:
	void PlaceFood(class AFood* Food);
	void ClearFood();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFood> FoodOnTable;
};
