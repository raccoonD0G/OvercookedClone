// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Waiter.h"
#include "AIControllers/StateAIController.h"
#include "AIStates/WaiterState.h"
#include "Actors/FinishStation.h"
#include "Actors/CustomerTable.h"
#include "Actors/Food.h"


AWaiter::AWaiter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AWaiter::BeginPlay()
{
	Super::BeginPlay();

	check(FinishStation);
	FinishStation->OnCookSuccess.AddDynamic(this, &AWaiter::OnCookSuccess);
}

void AWaiter::OnCookSuccess(const FOrder& SuccessOrder)
{
	TargetTable = SuccessOrder.CustomerTable;

	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	AWaiterState* WaiterState = Cast<AWaiterState>(StateAIController->GetAIState());
	check(WaiterState);

	WaiterState->SetCurrentState(EWaiterState::MoveToFinishStation);
}

void AWaiter::EndMoveToRandomPos()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	AWaiterState* WaiterState = Cast<AWaiterState>(StateAIController->GetAIState());
	check(WaiterState);

	WaiterState->SetCurrentState(EWaiterState::WaitForNextMove);
}

void AWaiter::EndWaitForNextMove()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	AWaiterState* WaiterState = Cast<AWaiterState>(StateAIController->GetAIState());
	check(WaiterState);

	WaiterState->SetCurrentState(EWaiterState::MoveToRandomPos);
}


void AWaiter::EndMoveToFinishStation()
{
	FoodOnHand = FinishStation->GetFoodOnTable();
	FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	FoodOnHand->AttachToComponent(GetMesh(), AttachmentTransformRules, TEXT("Hand"));
	FinishStation->SetFoodOnTable(nullptr);

	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	AWaiterState* WaiterState = Cast<AWaiterState>(StateAIController->GetAIState());
	check(WaiterState);

	WaiterState->SetCurrentState(EWaiterState::MoveToTable);
}

void AWaiter::EndMoveToTable()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	AWaiterState* WaiterState = Cast<AWaiterState>(StateAIController->GetAIState());
	check(WaiterState);

	WaiterState->SetCurrentState(EWaiterState::MoveToRandomPos);

	check(FoodOnHand);
	TargetTable->PlaceFood(FoodOnHand);
	TargetTable = nullptr;
}
