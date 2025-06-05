// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/TeamBuildingGameState.h"
#include "Net/UnrealNetwork.h"

void ATeamBuildingGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATeamBuildingGameState, PlayerCount);

}

void ATeamBuildingGameState::SetPlayerCount(int32 NewPlayerCount)
{
	PlayerCount = NewPlayerCount;
	OnPlayerCountChange.Broadcast(PlayerCount);
}

void ATeamBuildingGameState::OnRep_PlayerCount()
{
	OnPlayerCountChange.Broadcast(PlayerCount);
}
