// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CustomerTable.h"
#include "Actors/Food.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


ACustomerTable::ACustomerTable()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}
	
	

void ACustomerTable::PlaceFood(AFood* Food)
{
	FoodOnTable = Food;
	FoodOnTable->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("TableTop"));
	OnFoodPlaced.Broadcast();
}

void ACustomerTable::ClearFood()
{
	if (FoodOnTable)
	{
		FoodOnTable->Destroy();
		FoodOnTable = nullptr;
	}
}

void ACustomerTable::OrderIgnored()
{
	OnOrderIgnored.Broadcast();
}

