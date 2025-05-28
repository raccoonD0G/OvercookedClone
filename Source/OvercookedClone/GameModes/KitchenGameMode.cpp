// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/KitchenGameMode.h"
#include "PlayerStarts/KitchenPlayerStart.h"
#include "Characters/PlayerCharacter.h"
#include "Actors/FinishStation.h"
#include "Actors/CashRegister.h"

APawn* AKitchenGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
    AKitchenPlayerStart* KitchenPlayerStart = Cast<AKitchenPlayerStart>(StartSpot);

    APawn* SpawnedPawn = Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);

    if (KitchenPlayerStart && SpawnedPawn)
    {
        APlayerCharacter* Player = Cast<APlayerCharacter>(SpawnedPawn);
        if (Player)
        {
            Player->SetFinishStation(KitchenPlayerStart->GetFinishStation());
        }
    }

    return SpawnedPawn;
}