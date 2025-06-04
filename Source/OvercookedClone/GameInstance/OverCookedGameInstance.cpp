// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/OvercookedGameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Online/OnlineSessionNames.h"
#include "Engine/Engine.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UOvercookedGameInstance::Init()
{
    Super::Init();

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

void UOvercookedGameInstance::HostSession(FName SessionName)
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
            SessionSettings.NumPublicConnections = 1;
            SessionSettings.bShouldAdvertise = true;
            SessionSettings.bUsesPresence = true;
            SessionSettings.bAllowJoinInProgress = true;

            SessionInterface->CreateSession(0, SessionName, SessionSettings);
        }
    }
}

void UOvercookedGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
        }
    }

    if (bWasSuccessful)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            World->ServerTravel("/Game/Maps/TeamBuildingMap?listen");
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("세션 생성 실패"));
    }
}

void UOvercookedGameInstance::JoinSession()
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionSearch = MakeShareable(new FOnlineSessionSearch());
            SessionSearch->bIsLanQuery = false;
            SessionSearch->MaxSearchResults = 20;
            SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

            OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UOvercookedGameInstance::OnFindSessionsComplete);
            OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

            SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
        }
    }
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

        // 첫 번째 세션에 바로 참가
        const FOnlineSessionSearchResult& Result = SessionSearch->SearchResults[0];

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
            APlayerController* PC = GetFirstLocalPlayerController();
            if (PC)
            {
                PC->ClientTravel(ConnectString, TRAVEL_Absolute);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("접속 주소를 얻을 수 없습니다."));
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

            const FName SessionName = NAME_GameSession;

            // 세션 존재 여부 확인 후 제거
            if (SessionInterface->GetNamedSession(SessionName) != nullptr)
            {
                UE_LOG(LogTemp, Log, TEXT("세션 제거 시도 중..."));
                SessionInterface->DestroySession(SessionName);
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
