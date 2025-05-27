// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KitchenHUD.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AKitchenHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetFinishStation(class AFinishStation* NewFisishStation) { FinishStation = NewFisishStation; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AFinishStation> FinishStation;
};
