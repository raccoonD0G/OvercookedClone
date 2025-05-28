// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Order.h"
#include "Interfaces/TableOccupyInterface.h"
#include "Interfaces/MoveToCachRegisterInterface.h"
#include "Interfaces/MoveToTableInterface.h"
#include "Interfaces/EatInterface.h"
#include "Interfaces/ExitInterface.h"
#include "interfaces/WaitForFoodInterface.h"
#include "Customer.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACustomer : public ACharacter, public ITableOccupyInterface, public IMoveToCachRegisterInterface, public IMoveToTableInterface, public IWaitForFoodInterface, public IEatInterface, public IExitInterface
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

public:
	virtual void EndMoveToCachRegister() override;
	virtual void EndMoveToTable() override;
	virtual void EndWaitingForFood() override;
	virtual void EndEating() override;
	virtual void EndExiting() override;
};
