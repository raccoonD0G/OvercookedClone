// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CustomerSpawner.h"
#include "Characters/Customer.h"
#include "Engine/World.h"
#include "TimerManager.h"

ACustomerSpawner::ACustomerSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACustomerSpawner::BeginPlay()
{
	Super::BeginPlay();

	// 20�ʿ� �� ���� �ݺ� ����
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
	GetWorld()->SpawnActor<ACustomer>(CustomerClass, SpawnLocation, SpawnRotation, SpawnParams);
}
