// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Order.h"
#include "Interfaces/TableOccupyInterface.h"
#include "Customer.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACustomer : public ACharacter, public ITableOccupyInterface
{
	GENERATED_BODY()

public:
	ACustomer();
	
public:
	void Init(class ACashRegister* NewCashRegister);

	UFUNCTION(BlueprintCallable)
	void GenerateOrder();

	FORCEINLINE class ACustomerTable* GetTargetTable() const { return TargetTable; }
	FORCEINLINE class ACashRegister* GetTargetRegister() const { return CashRegister; }

private:
	FORCEINLINE void SetTargetTable(class ACustomerTable* NewTable) { TargetTable = NewTable; }
	FORCEINLINE void SetCashRegister(class ACashRegister* NewCashRegister) { CashRegister = NewCashRegister; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACustomerTable> TargetTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACashRegister> CashRegister;

public:
	UFUNCTION()
	virtual void OccupyTable(class ACustomerTable* Table) override;

	virtual class ACustomerTable* OccupiedTable() const override;
};
