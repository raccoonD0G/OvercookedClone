// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawner.h"
#include "Kismet/GameplayStatics.h"


ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnInterval = 7.0f;
	SpawnLocation = FVector::ZeroVector;
	SpawnRotation = FRotator::ZeroRotator;
	MaxSpawnedActorCount = 3;
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
	if (SpawnedActorCount < MaxSpawnedActorCount)
	{
		AActor* SpawnedActor = SpawnActorDeffered();
		if (!SpawnedActor) return;

		FTransform SpawnTransform(SpawnRotation, SpawnLocation);
		UGameplayStatics::FinishSpawningActor(SpawnedActor, SpawnTransform);
		SpawnedActor->OnDestroyed.AddDynamic(this, &ASpawner::DecreaseSpawnedActorCount);
		SpawnedActorCount++;
	}
}

void ASpawner::DecreaseSpawnedActorCount(AActor* DestroyedActor)
{
	SpawnedActorCount--;
}

AActor* ASpawner::SpawnActorDeffered()
{
	if (!ActorClass) return nullptr;

	FTransform SpawnTransform(SpawnRotation, SpawnLocation);
	AActor* SpawnedActor = Cast<AActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		this,
		ActorClass,
		SpawnTransform
	));

	return SpawnedActor;
}
