// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawner();

protected:
	virtual void BeginPlay() override;

protected:
	virtual AActor* SpawnActorDeffered();

private:
	void SpawnActor();

protected:
	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor> ActorClass;

private:
	UFUNCTION()
	void DecreaseSpawnedActorCount(AActor* DestroyedActor);

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnInterval;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 SpawnedActorCount;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 MaxSpawnedActorCount;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FRotator SpawnRotation;
	
};
