// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KitchenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AKitchenPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	
};
