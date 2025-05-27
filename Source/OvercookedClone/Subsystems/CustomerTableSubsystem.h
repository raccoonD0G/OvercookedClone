// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CustomerTableSubsystem.generated.h"


/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API UCustomerTableSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSet<TObjectPtr<class ACustomerTable>> NotOccupiedTables;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSet<TObjectPtr<class ACustomerTable>> OccupiedTables;

public:
	/// <summary>
	/// Sit on NotOccupiedTable
	/// </summary>
	/// <param name="TableOccupyInterface">Actor to occupy seat</param>
	/// <returns>Return false if all seats occupied</returns>
	bool OccupyTable(class ITableOccupyInterface* TableOccupyInterface);

	/// <summary>
	/// Unoccupy Table
	/// </summary>
	/// <param name="TableOccupyInterface">Actor to unoccupy seat</param>
	void UnoccupiedTable(class ITableOccupyInterface* TableOccupyInterface);

};
