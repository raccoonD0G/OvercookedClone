// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/PlayerControllerBase.h"
#include "GameInstance/OvercookedGameInstance.h"

APlayerControllerBase::APlayerControllerBase()
{
	;
}

void APlayerControllerBase::Client_RequestjoinSession_Implementation()
{
	UOvercookedGameInstance* OvercookedGameInstance = Cast<UOvercookedGameInstance>(GetGameInstance());
	if (OvercookedGameInstance)
	{
		OvercookedGameInstance->JoinSession();
	}
}