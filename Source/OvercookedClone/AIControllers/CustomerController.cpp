// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/CustomerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Customer.h"
#include "Actors/CashRegister.h"
#include "Actors/CustomerTable.h"

void ACustomerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ACustomerState* CustomerState = Cast<ACustomerState>(GetAIState());
	check(CustomerState);

	CustomerState->OnCurrentStateChange.AddDynamic(this, &ACustomerController::OnCurrentStateChange);
	CustomerState->SetCurrentState(ECustomerState::MoveToRegister);
}

void ACustomerController::OnCurrentStateChange(ECustomerState NewState)
{
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();
	check(BlackboardComp);

	BlackboardComp->SetValueAsEnum(TEXT("CustomerState"), static_cast<uint8>(NewState));

	ACustomer* Customer = Cast<ACustomer>(GetPawn());

	check(Customer);

	switch (NewState)
	{
	case ECustomerState::MoveToRegister:
		BlackboardComp->SetValueAsObject(TEXT("TargetRegister"), Customer->GetTargetRegister());
		break;
	case ECustomerState::MoveToTable:
		BlackboardComp->SetValueAsObject(TEXT("TargetTable"), Customer->GetTargetTable());
		break;
	case ECustomerState::Eating:
		break;
	case ECustomerState::Exiting:
		break;
	}
}
