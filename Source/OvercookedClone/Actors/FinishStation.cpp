// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FinishStation.h"
#include "Actors/CustomerTable.h"
#include "Actors/Food.h"


// Sets default values
AFinishStation::AFinishStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFinishStation::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnClicked.AddDynamic(this, &AFinishStation::OnActorClicked);

}

// TODO
void AFinishStation::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	AFood* NewFood = GetWorld()->SpawnActor<AFood>();
	CurrentOrder.CustomerTable->PlaceFood(NewFood);
}