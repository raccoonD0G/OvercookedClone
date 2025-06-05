// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ResultWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameStates/ResultGameState.h"
#include "GameInstance/OvercookedGameInstance.h"
#include "OnlineSubsystem.h"

void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (AResultGameState* ResultGameState = GetWorld()->GetGameState<AResultGameState>())
    {
        SetResultScoreText(ResultGameState->GetScore());
        ResultGameState->OnScoreChange.AddDynamic(this, &UResultWidget::SetResultScoreText);
    }

    BackToMainButton->OnClicked.AddDynamic(this, &UResultWidget::OpenEntryLevel);
}

void UResultWidget::OpenEntryLevel()
{
    const FString ResultMapPath = "/Game/Maps/EntryMap";
    APlayerController* PlayerController = GetOwningPlayer();
    if (!PlayerController) return;

    UWorld* World = GetWorld();
    if (!World) return;

    UOvercookedGameInstance* OvercookedGameInstance = Cast<UOvercookedGameInstance>(GetGameInstance());
    if (!OvercookedGameInstance) return;


    switch (PlayerController->GetNetMode())
    {
    case NM_Standalone:
        UGameplayStatics::OpenLevel(this, FName("EntryMap"));
        break;

    case NM_ListenServer:
        OvercookedGameInstance->DestroySession();
        PlayerController->ClientTravel(ResultMapPath, TRAVEL_Absolute);
        break;

    case NM_Client:
        OvercookedGameInstance->DestroySession();
        PlayerController->ClientTravel(ResultMapPath, TRAVEL_Absolute);
        break;

    default:
        UE_LOG(LogTemp, Warning, TEXT("OpenEntryLevel called in unexpected NetMode"));
        break;
    }
}



void UResultWidget::SetResultScoreText(float Score)
{
    ResultScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), static_cast<int32>(Score))));
}

