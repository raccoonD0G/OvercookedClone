// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WaiterController.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AWaiterController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
};
