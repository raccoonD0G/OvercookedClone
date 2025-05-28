// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CustomerSpawner.h"
#include "Characters/Customer.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Subsystems/CustomerTableSubsystem.h"
#include "Actors/CustomerTable.h"
#include "Actors/CashRegister.h"
#include "Kismet/GameplayStatics.h"

ACustomerSpawner::ACustomerSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

AActor* ACustomerSpawner::SpawnActorDeffered()
{
	AActor* SpawnedActor = Super::SpawnActorDeffered();

	UCustomerTableSubsystem* TableSubsystem = GetWorld()->GetSubsystem<UCustomerTableSubsystem>();
	if (!TableSubsystem)
	{
		GetWorld()->DestroyActor(SpawnedActor);
		return nullptr;
	}

	if (TableSubsystem->LeftSeatsNum() == 0)
	{
		GetWorld()->DestroyActor(SpawnedActor);
		return nullptr;
	}

	if (!SpawnedActor) return nullptr;

	ACustomer* Customer = Cast<ACustomer>(SpawnedActor);

	if (!Customer)
	{
		GetWorld()->DestroyActor(SpawnedActor);
		return nullptr;
	}

	TableSubsystem->OccupyTable(Customer);
	Customer->Init(CashRegister);

	return Customer;
}

