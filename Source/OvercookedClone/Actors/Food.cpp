// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AFood::AFood()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	FoodMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMeshComponent"));
	FoodMeshComponent->SetupAttachment(RootComponent);
	FoodMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	
	DishMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DishMeshComponent"));
	DishMeshComponent->SetupAttachment(RootComponent);
	DishMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	
	bReplicates = true;
}

