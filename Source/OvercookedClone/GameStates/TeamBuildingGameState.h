// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TeamBuildingGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerCountChange, int32, NewPlayerCount);

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API ATeamBuildingGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FOnPlayerCountChange OnPlayerCountChange;

	void SetPlayerCount(int32 NewPlayerCount);
	FORCEINLINE int32 GetPlayerCount() const { return PlayerCount; }

private:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerCount, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 PlayerCount;

	UFUNCTION()
	void OnRep_PlayerCount();
};
