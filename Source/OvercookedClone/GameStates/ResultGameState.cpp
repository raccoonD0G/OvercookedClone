// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/ResultGameState.h"
#include "Net/UnrealNetwork.h"
#include "GameInstance/OvercookedGameInstance.h"

void AResultGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AResultGameState, Score);
}

void AResultGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UOvercookedGameInstance* OvercookedGameInstance = GetGameInstance<UOvercookedGameInstance>();
	if (OvercookedGameInstance)
	{
		Score = OvercookedGameInstance->GetScore();
		OnScoreChange.Broadcast(Score);
	}
}

void AResultGameState::OnRep_Score()
{
	OnScoreChange.Broadcast(Score);
}