// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawner.h"
#include "Kismet/GameplayStatics.h"


ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnInterval = 7.0f;
	SpawnCenterLocation = FVector::ZeroVector;
	SpawnCenterRotation = FRotator::ZeroRotator;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnActor();
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ASpawner::SpawnActor,
		SpawnInterval,
		true
	);
	
}

void ASpawner::SpawnActor()
{
	AActor* SpawnedActor = SpawnActorDeffered();
	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, SpawnTransform);
}

AActor* ASpawner::SpawnActorDeffered()
{
	if (!ActorClass) return nullptr;

	FTransform SpawnTransform(SpawnCenterRotation, SpawnCenterLocation);
	AActor* SpawnedActor = Cast<AActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		this,
		ActorClass,
		SpawnTransform
	));

	return SpawnedActor;
}
