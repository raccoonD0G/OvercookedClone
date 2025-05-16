// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CustomerSpawner.h"
#include "Characters/Customer.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Subsystem/CustomerTableSubsystem.h"
#include "Actors/CustomerTable.h"

ACustomerSpawner::ACustomerSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACustomerSpawner::BeginPlay()
{
	Super::BeginPlay();

	// 20초에 한 번씩 반복 실행
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ACustomerSpawner::SpawnCustomer,
		20.0f,
		true
	);
}

void ACustomerSpawner::SpawnCustomer()
{
	if (!CustomerClass) return;

	FVector SpawnLocation = FVector::ZeroVector; // (0,0,0)
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	ACustomer* Customer = GetWorld()->SpawnActor<ACustomer>(CustomerClass, SpawnLocation, SpawnRotation, SpawnParams);
	UCustomerTableSubsystem* TableSubsystem = GetWorld()->GetSubsystem<UCustomerTableSubsystem>();

	if (TableSubsystem)
	{
		ACustomerTable* Table = TableSubsystem->GetNotOccupiedTable();
		if (Table)
		{
			Customer->SetTargetTable(Table);
		}
		else
		{
			Customer->Destroy();
		}
	}
	
}
