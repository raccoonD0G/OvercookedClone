// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CustomerTable.h"
#include "Actors/Food.h"


ACustomerTable::ACustomerTable()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerTable::PlaceFood(AFood* Food)
{
	FoodOnTable = Food;
	FoodOnTable->SetActorLocation(GetActorLocation());
}

void ACustomerTable::ClearFood()
{
	FoodOnTable->Destroy();
	FoodOnTable = nullptr;
}

