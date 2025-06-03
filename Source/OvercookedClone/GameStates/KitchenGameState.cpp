// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStates/KitchenGameState.h"
#include "Net/UnrealNetwork.h"
#include "GameModes/KitchenGameMode.h"
#include "Components/TimerComponent.h"


AKitchenGameState::AKitchenGameState()
{
	MouseCount = 0;
	bIsSeatsFull = false;
	Score = 100.0f;
	
	MouseCountRatio = 0.1;
	SeatsFullRatio = 0.5;

	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	TimerComponent = CreateDefaultSubobject<UTimerComponent>(TEXT("TimerComponent"));
}

void AKitchenGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AKitchenGameState, MouseCount);
	DOREPLIFETIME(AKitchenGameState, bIsSeatsFull);
	DOREPLIFETIME(AKitchenGameState, Score);
}

void AKitchenGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AKitchenGameMode* KitchenGameMode = Cast<AKitchenGameMode>(GetWorld()->GetAuthGameMode());
		if (KitchenGameMode)
		{
			TimerComponent->OnTimerFinish.AddDynamic(KitchenGameMode, &AKitchenGameMode::OpenResultLevel);
		}
	}
}

void AKitchenGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		DecreaseScore(MouseCount * MouseCountRatio * DeltaSeconds);

		if (bIsSeatsFull)
		{
			DecreaseScore(SeatsFullRatio * DeltaSeconds);
		}
	}
}

void AKitchenGameState::IncreaseScore(float Amount)
{
	Score += Amount;
	Score = FMath::Clamp(Score, 0.0f, 100.0f);
}

void AKitchenGameState::DecreaseScore(float Amount)
{
	Score -= Amount;
	Score = FMath::Clamp(Score, 0.0f, 100.0f);
}
