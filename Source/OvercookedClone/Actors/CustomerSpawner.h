// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawner.h"
#include "CustomerSpawner.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACustomerSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:
	ACustomerSpawner();

protected:
	virtual AActor* SpawnActorDeffered() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class ACashRegister> CashRegister;
};
