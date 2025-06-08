// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/WaiterController.h"
#include "AIStates/WaiterState.h"
#include "Characters/Waiter.h"
#include "Actors/FinishStation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/CustomerTable.h"

void AWaiterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AWaiterState* WaiterState = Cast<AWaiterState>(GetAIState());
	check(WaiterState);

	WaiterState->OnCurrentStateChange.AddDynamic(this, &AWaiterController::OnCurrentStateChange);
	WaiterState->SetCurrentState(EWaiterState::MoveToRandomPos);
}

void AWaiterController::OnCurrentStateChange(EWaiterState NewState)
{
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	check(BlackboardComp);

	BlackboardComp->SetValueAsEnum(TEXT("WaiterState"), static_cast<uint8>(NewState));

	AWaiter* Waiter = Cast<AWaiter>(GetPawn());

	check(Waiter);

	switch (NewState)
	{
	case EWaiterState::MoveToRandomPos:
		break;
	case EWaiterState::WaitForNextMove:
		break;
	case EWaiterState::MoveToFinishStation:
		BlackboardComp->SetValueAsObject(TEXT("FinishStation"), Waiter->GetFinishStation());
		break;
	case EWaiterState::MoveToTable:
		BlackboardComp->SetValueAsObject(TEXT("TargetTable"), Waiter->GetTargetTable());
		break;
	}
}

