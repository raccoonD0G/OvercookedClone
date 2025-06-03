// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TeamBuildingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API ATeamBuildingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
};
