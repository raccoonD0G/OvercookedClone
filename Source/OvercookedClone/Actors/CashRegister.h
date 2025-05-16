// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Recipe.h"
#include "Order.h"
#include "Interfaces/InteractableInterface.h"
#include "CashRegister.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACashRegister : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	ACashRegister();	

public:
	virtual void Interact_Implementation(AActor* Caller) override;

	void AddOrder(FOrder Order);
	void DeleteOrder();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FOrder> Orders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFinishStation> FinishStation;

};
