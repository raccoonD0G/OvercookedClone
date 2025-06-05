// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/OvercookedGameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Online/OnlineSessionNames.h"
#include "Engine/Engine.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "PlayerControllers/PlayerControllerBase.h"
#include "Gameframework/GameModeBase.h"

void UOvercookedGameInstance::Init()
{
    Super::Init();

    if (GEngine)
    {
        UGameUserSettings* Settings = GEngine->GetGameUserSettings();
        if (Settings)
        {
            Settings->SetFullscreenMode(EWindowMode::Windowed);
            Settings->SetScreenResolution(FIntPoint(1280, 720));
            Settings->ApplySettings(false);
        }
    }

    FString Nickname = GetSteamNickname();
    if (!Nickname.IsEmpty())
    {
        UE_LOG(LogTemp, Log, TEXT("Logged in as %s"), *Nickname);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Steam nickname not found"));
    }
}

FString UOvercookedGameInstance::GetSteamNickname() const
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (!Subsystem)
    {
        return FString();
    }

    IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
    if (!Identity.IsValid())
    {
        return FString();
    }

    TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(0);
    if (!UserId.IsValid())
    {
        return FString();
    }

    return Identity->GetPlayerNickname(*UserId);
}

void UOvercookedGameInstance::HostSession()
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOvercookedGameInstance::OnCreateSessionComplete);
            OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

            FOnlineSessionSettings SessionSettings;
            SessionSettings.bIsLANMatch = false;
            SessionSettings.bIsDedicated = false;
            SessionSettings.NumPublicConnections = 2;
            SessionSettings.bShouldAdvertise = true;
            SessionSettings.bUseLobbiesIfAvailable = true;
            SessionSettings.bUsesPresence = true;
            SessionSettings.bAllowJoinInProgress = true;
            SessionSettings.bAllowJoinViaPresence = true;
            SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
            
            SessionSettings.Set(FName("GameId"), FString("OvercookedClone"), EOnlineDataAdvertisementType::ViaOnlineService);
            SessionSettings.Set(FName("roomName"), FString("TestRoom"), EOnlineDataAdvertisementType::ViaOnlineService);

            SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
        }
    }
}


void UOvercookedGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (!Subsystem) return;

    IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
    }

    if (bWasSuccessful)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            World->ServerTravel("/Game/Maps/TeamBuildingMap?listen");
        }
    }
}


void UOvercookedGameInstance::JoinSession()
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (!Subsystem) return;

    IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
    if (!SessionInterface.IsValid()) return;

    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->bIsLanQuery = false;
    SessionSearch->MaxSearchResults = 20;
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

    SessionSearch->QuerySettings.Set(FName("GameId"), FString("OvercookedClone"), EOnlineComparisonOp::Equals);

    OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UOvercookedGameInstance::OnFindSessionsComplete);
    OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UOvercookedGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (!Subsystem) return;

    IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
    }

    if (bWasSuccessful && SessionSearch.IsValid() && SessionSearch->SearchResults.Num() > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("세션 %d개 발견"), SessionSearch->SearchResults.Num());

        for (int32 Index = 0; Index < SessionSearch->SearchResults.Num(); ++Index)
        {
            FOnlineSessionSearchResult Result = SessionSearch->SearchResults[Index];

            FString RoomName, GameId;
            Result.Session.SessionSettings.Get(FName("roomName"), RoomName);
            Result.Session.SessionSettings.Get(FName("GameId"), GameId);

            FString SessionIdStr = Result.GetSessionIdStr();
            FString OwnerName = Result.Session.OwningUserName;

            UE_LOG(LogTemp, Log, TEXT("세션[%d]: Owner=%s, RoomName=%s, GameId=%s, SessionId=%s"),
                Index, *OwnerName, *RoomName, *GameId, *SessionIdStr);
        }

        // 참가 시도
        FOnlineSessionSearchResult Result = SessionSearch->SearchResults[0];

        FOnlineSessionSearchResult& ModifiableSessionResult = const_cast<FOnlineSessionSearchResult&>(Result);
        FOnlineSessionSettings& SessionSettings = ModifiableSessionResult.Session.SessionSettings;
        SessionSettings.bUsesPresence = true;
        SessionSettings.bUseLobbiesIfAvailable = true;

        OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UOvercookedGameInstance::OnJoinSessionComplete);
        OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

        SessionInterface->JoinSession(0, NAME_GameSession, Result);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("세션을 찾을 수 없습니다."));
    }
}

void UOvercookedGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (!Subsystem) return;

    IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
    if (SessionInterface.IsValid())
    {
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

        FString ConnectString;
        if (SessionInterface->GetResolvedConnectString(SessionName, ConnectString))
        {
            UE_LOG(LogTemp, Log, TEXT("Resolved Connect String: %s"), *ConnectString);

            APlayerControllerBase* PlayerControllerBase = Cast<APlayerControllerBase>(GetFirstLocalPlayerController());
            if (PlayerControllerBase)
            {
                PlayerControllerBase->SetConnectString(ConnectString);
                PlayerControllerBase->ClientTravel(ConnectString, TRAVEL_Absolute, true);
                UE_LOG(LogTemp, Log, TEXT("Done Connect String: %s"), *ConnectString);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("접속 주소 없음."));
        }
    }
}

void UOvercookedGameInstance::DestroySession()
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UOvercookedGameInstance::OnDestroySessionComplete);
            OnDestroySessionCompleteDelegateHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);

            if (SessionInterface->GetNamedSession(NAME_GameSession) != nullptr)
            {
                UE_LOG(LogTemp, Log, TEXT("세션 제거 시도 중..."));
                SessionInterface->DestroySession(NAME_GameSession);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("제거할 세션이 없습니다."));
            }
        }
    }
}

void UOvercookedGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
        }
    }

    if (bWasSuccessful)
    {
        UE_LOG(LogTemp, Log, TEXT("세션이 성공적으로 제거되었습니다."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("세션 제거 실패."));
    }
}
