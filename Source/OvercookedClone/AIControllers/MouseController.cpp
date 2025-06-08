// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/MouseController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Mouse.h"

void AMouseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMouseState* MouseState = Cast<AMouseState>(GetAIState());
	check(MouseState);

	MouseState->OnCurrentStateChange.AddDynamic(this, &AMouseController::OnCurrentStateChange);
	MouseState->SetCurrentState(EMouseState::MoveToRandomPos);
}

void AMouseController::OnCurrentStateChange(EMouseState NewState)
{
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	check(BlackboardComp);

	BlackboardComp->SetValueAsEnum(TEXT("MouseState"), static_cast<uint8>(NewState));

	AMouse* Mouse = Cast<AMouse>(GetPawn());

	check(Mouse);

	switch (NewState)
	{
	case EMouseState::MoveToRandomPos:
		break;
	case EMouseState::WaitForNextMove:
		break;
	}
}

