// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/PlayerControllerBase.h"
#include "ResultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AResultPlayerController : public APlayerControllerBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
};
