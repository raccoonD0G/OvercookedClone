// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/TeamBuildingGameMode.h"
#include "GameStates/TeamBuildingGameState.h"

ATeamBuildingGameMode::ATeamBuildingGameMode()
{
	PlayerCount = 0;
}

void ATeamBuildingGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerCount++;

	ATeamBuildingGameState* TeamBuildingGameState = GetWorld()->GetGameState<ATeamBuildingGameState>();
	if (TeamBuildingGameState)
	{
		TeamBuildingGameState->SetPlayerCount(PlayerCount);
	}
}

void ATeamBuildingGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	PlayerCount = FMath::Max(0, PlayerCount - 1);

	ATeamBuildingGameState* TeamBuildingGameState = GetWorld()->GetGameState<ATeamBuildingGameState>();
	if (TeamBuildingGameState)
	{
		TeamBuildingGameState->SetPlayerCount(PlayerCount);
	}
}