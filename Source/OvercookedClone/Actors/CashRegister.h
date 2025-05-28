// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Recipe.h"
#include "Order.h"
#include "Actors/InteractableBase.h"
#include "CashRegister.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACashRegister : public AInteractableBase
{
	GENERATED_BODY()
	
public:	
	ACashRegister();	

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void Interact(AActor* Caller) override;

	UFUNCTION(BlueprintCallable)
	void AddOrder(FOrder Order);

	UFUNCTION(BlueprintCallable)
	void DeleteOrder();

private:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FOrder> Orders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFinishStation> FinishStation;

};
