// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TeamBuildingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API ATeamBuildingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATeamBuildingGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlayerCount;
};
