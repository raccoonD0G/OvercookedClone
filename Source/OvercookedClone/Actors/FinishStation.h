// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Order.h"
#include "FinishStation.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API AFinishStation : public AActor
{
	GENERATED_BODY()
	
public:	
	AFinishStation();

protected:
	virtual void PostInitializeComponents() override;
	
public:
	UFUNCTION()
	void OnActorClicked(AActor* TouchedActor, FKey ButtonPressed);

	FORCEINLINE void SetCurrentOrder(FOrder NewOrder) { CurrentOrder = NewOrder; }

private:
	FOrder CurrentOrder;
};
