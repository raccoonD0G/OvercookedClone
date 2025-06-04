// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OvercookedGameInstance.generated.h"



/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API UOvercookedGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
        virtual void Init() override;

        FORCEINLINE void SetScore(float NewScore) { Score = NewScore; }
        FORCEINLINE float GetScore() const { return Score; }

        /** Get player's Steam nickname */
        UFUNCTION(BlueprintCallable, Category="Steam")
        FString GetSteamNickname() const;

private:
	float Score;

public:
    UFUNCTION(BlueprintCallable)
    void HostSession(FName SessionName);

    UFUNCTION(BlueprintCallable)
    void JoinSession();

    UFUNCTION(BlueprintCallable)
    void DestroySession();

private:
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;

    FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
    FDelegateHandle OnFindSessionsCompleteDelegateHandle;

    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
    FDelegateHandle OnJoinSessionCompleteDelegateHandle;

    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
    FDelegateHandle OnDestroySessionCompleteDelegateHandle;

    TSharedPtr<FOnlineSessionSearch> SessionSearch;

    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsComplete(bool bWasSuccessful);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
    void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
};
