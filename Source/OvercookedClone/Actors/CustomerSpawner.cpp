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

	UCustomerTableSubsystem* TableSubsystem = GetWorld()->GetSubsystem<UCustomerTableSubsystem>();
	if (!TableSubsystem) return;

	ACustomerTable* Table = TableSubsystem->GetNotOccupiedTable();
	if (!Table) return;

	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	ACustomer* Customer = Cast<ACustomer>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		this,
		CustomerClass,
		SpawnTransform
	));

	if (!Customer) return;

	Customer->Init(Table, CashRegister);

	UGameplayStatics::FinishSpawningActor(Customer, SpawnTransform);
}

