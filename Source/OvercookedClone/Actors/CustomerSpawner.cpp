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
	SpawnInterval = 7.0f;
}

void ACustomerSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnCustomer();
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ACustomerSpawner::SpawnCustomer,
		SpawnInterval,
		true
	);
}

void ACustomerSpawner::SpawnCustomer()
{
	if (!CustomerClass) return;

	UCustomerTableSubsystem* TableSubsystem = GetWorld()->GetSubsystem<UCustomerTableSubsystem>();
	if (!TableSubsystem) return;

	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	ACustomer* Customer = Cast<ACustomer>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		this,
		CustomerClass,
		SpawnTransform
	));

	if (!Customer) return;

	TableSubsystem->OccupyTable(Customer);
	Customer->Init(CashRegister);

	UGameplayStatics::FinishSpawningActor(Customer, SpawnTransform);
}

