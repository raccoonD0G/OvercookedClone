// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Order.h"
#include "Customer.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomer();
	
public:
	void Init(class ACustomerTable* NewTable, class ACashRegister* NewCashRegister);

	UFUNCTION(BlueprintCallable)
	void GenerateOrder();

	FORCEINLINE void SetTargetTable(class ACustomerTable* NewTable) { TargetTable = NewTable; }
	FORCEINLINE void SetCashRegister(class ACashRegister* NewCashRegister) { CashRegister = NewCashRegister; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACustomerTable> TargetTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACashRegister> CashRegister;
};
