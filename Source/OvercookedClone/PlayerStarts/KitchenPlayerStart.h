// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "KitchenPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AKitchenPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:
	FORCEINLINE class AFinishStation* GetFinishStation() { return FinishStation; }
	FORCEINLINE class ACashRegister* GetCashRegister() { return CashRegister; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFinishStation> FinishStation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACashRegister> CashRegister;
};
