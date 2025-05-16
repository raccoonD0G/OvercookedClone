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
	class ACustomerTable* GetNotOccupiedTable();
};
