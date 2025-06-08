// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/StateAICharacter.h"
#include "Interfaces/MoveToRandomPosInterface.h"
#include "Interfaces/WaitForNextMoveInterface.h"
#include "Interfaces/MoveToFinishStationInterface.h"
#include "Interfaces/MoveToTableInterface.h"
#include "Order.h"
#include "Waiter.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API AWaiter : public AStateAICharacter, public IMoveToRandomPosInterface, public IWaitForNextMoveInterface, public IMoveToFinishStationInterface, public IMoveToTableInterface
{
	GENERATED_BODY()

public:
	AWaiter();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE class AFinishStation* GetFinishStation() const { return FinishStation; }
	FORCEINLINE class ACustomerTable* GetTargetTable() const { return TargetTable; }

	UFUNCTION()
	void OnCookSuccess(const FOrder& SuccessOrder);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFinishStation> FinishStation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACustomerTable> TargetTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFood> FoodOnHand;

public:
	virtual void EndMoveToRandomPos() override;

	virtual void EndWaitForNextMove() override;

	virtual void EndMoveToFinishStation() override;

	virtual void EndMoveToTable() override;
};
