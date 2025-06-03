// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/KitchenGameMode.h"
#include "PlayerStarts/KitchenPlayerStart.h"
#include "Characters/PlayerCharacter.h"
#include "Actors/FinishStation.h"
#include "Actors/CashRegister.h"
#include "GameInstance/OvercookedGameInstance.h"
#include "GameStates/KitchenGameState.h"
#include "Kismet/GameplayStatics.h"

void AKitchenGameMode::OpenResultLevel()
{
    SaveScore();

    const FString ResultMapPath = "/Game/Maps/ResultMap";

    switch (GetNetMode())
    {
        case NM_Standalone:
            UGameplayStatics::OpenLevel(this, FName("ResultMap"));
            break;

        case NM_ListenServer:
            GetWorld()->ServerTravel(ResultMapPath + "?listen");
            break;

        case NM_DedicatedServer:
            GetWorld()->ServerTravel(ResultMapPath);
            break;

        default:
            UE_LOG(LogTemp, Warning, TEXT("OpenResultLevel called on a client"));
            break;
    }
}

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

void AKitchenGameMode::SaveScore()
{
    AKitchenGameState* KitchenGameState = GetGameState<AKitchenGameState>();
    if (KitchenGameState)
    {
        UOvercookedGameInstance* OvercookedGameInstance = Cast<UOvercookedGameInstance>(GetGameInstance());
        OvercookedGameInstance->SetScore(KitchenGameState->GetScore());
    }
}
