// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerControllerBase();

public:
	UFUNCTION(Client, Reliable)
	void Client_RequestjoinSession();

	FORCEINLINE FString GetConnectString() const { return ConnectString; }
	FORCEINLINE void SetConnectString(FString NewConnectString) { ConnectString = NewConnectString; }

private:
	FString ConnectString;
};
