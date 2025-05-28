// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FinishStationWidget.h"
#include "Components/Button.h"
#include "Characters/PlayerCharacter.h"
#include "Actors/FinishStation.h"

void UFinishStationWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (FinishStationButton)
    {
        FinishStationButton->OnClicked.AddDynamic(this, &UFinishStationWidget::OnFinishStationClicked);
    }
}