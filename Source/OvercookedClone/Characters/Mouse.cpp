// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Mouse.h"
#include "GameStates/KitchenGameState.h"
#include "Interfaces/DestroyMouseInterface.h"
#include "Components/InteractComponent.h"
#include "AIControllers/StateAIController.h"
#include "AIStates/MouseState.h"

AMouse::AMouse()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
	InteractComponent->SetupAttachment(RootComponent);
}

void AMouse::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InteractComponent->OnInteract.AddDynamic(this, &AMouse::Interact);
}

void AMouse::BeginPlay()
{
	Super::BeginPlay();

	AKitchenGameState* KitchenGameState = GetWorld()->GetGameState<AKitchenGameState>();
	if (KitchenGameState)
	{
		KitchenGameState->IncreaseMouseCount();
	}
}

void AMouse::Interact(AActor* Caller)
{
	if (Caller && Caller->GetClass()->ImplementsInterface(UDestroyMouseInterface::StaticClass()))
	{
		IDestroyMouseInterface::Execute_DestroyMouse(Caller, this);
	}
}

void AMouse::EndMoveToRandomPos()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	AMouseState* MouseState = Cast<AMouseState>(StateAIController->GetAIState());
	check(MouseState);

	MouseState->SetCurrentState(EMouseState::WaitForNextMove);
}

void AMouse::EndWaitForNextMove()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	AMouseState* MouseState = Cast<AMouseState>(StateAIController->GetAIState());
	check(MouseState);

	MouseState->SetCurrentState(EMouseState::MoveToRandomPos);
}
