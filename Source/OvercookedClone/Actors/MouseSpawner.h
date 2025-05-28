// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawner.h"
#include "MouseSpawner.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AMouseSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:
	AMouseSpawner();

protected:
	virtual AActor* SpawnActorDeffered() override;
	
private:
	FTransform GetRandomNavMeshTransform(float Radius);

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SpawnRadius;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector SpawnCenterLocation;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FRotator SpawnCenterRotation;
};
