// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TeamBulidingWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSessionSettings.h"
#include "GameStates/TeamBuildingGameState.h"
#include "GameInstance/OvercookedGameInstance.h"
#include "PlayerControllers/PlayerControllerBase.h"

void UTeamBulidingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GameStartButton)
	{
		GameStartButton->OnClicked.AddDynamic(this, &UTeamBulidingWidget::OnGameStartButtonClicked);
	}

	ATeamBuildingGameState* TeamBuildingGameState = GetWorld()->GetGameState<ATeamBuildingGameState>();
	if (TeamBuildingGameState)
	{
		TeamBuildingGameState->OnPlayerCountChange.AddDynamic(this, &UTeamBulidingWidget::UpdatePlayerCount);
		UpdatePlayerCount(TeamBuildingGameState->GetPlayerCount());
	}
}

void UTeamBulidingWidget::OnGameStartButtonClicked()
{
	UWorld* World = GetWorld();
	if (World && World->GetFirstPlayerController()->HasAuthority())
	{
		if (AGameModeBase* GameMode = World->GetAuthGameMode())
		{
			GameMode->bUseSeamlessTravel = true;
		}

		GetWorld()->ServerTravel("/Game/Maps/KitchenMap?listen");
	}
}

void UTeamBulidingWidget::UpdatePlayerCount(int32 NewPlayerCount)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem) return;

	IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
	if (!SessionInterface.IsValid()) return;

	FNamedOnlineSession* Session = SessionInterface->GetNamedSession(NAME_GameSession);
	if (Session)
	{
		int32 MaxPlayers = Session->SessionSettings.NumPublicConnections;

		if (PlayerCountText)
		{
			PlayerCountText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d Players"), NewPlayerCount, MaxPlayers)));
		}
	}
}
