// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomerSpawner.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACustomerSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	ACustomerSpawner();

protected:
	virtual void BeginPlay() override;

private:
	void SpawnCustomer();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACustomer> CustomerClass;

	FTimerHandle SpawnTimerHandle;
};
