// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Customer.h"
#include "Actors/CashRegister.h"
#include "UObject/EnumProperty.h"
#include "Subsystems/CustomerTableSubsystem.h"
#include "AIController/StateAIController.h"
#include "AIStates/CustomerState.h"

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomer::Init(ACashRegister* NewCashRegister)
{
	SetCashRegister(NewCashRegister);
}

void ACustomer::GenerateOrder()
{
	FOrder NewOrder;
	NewOrder.CustomerTable = TargetTable;
	UEnum* EnumPtr = StaticEnum<ERecipeType>();
	NewOrder.RecipeType = static_cast<ERecipeType>(FMath::RandRange(1, EnumPtr->NumEnums() - 1));
	CashRegister->AddOrder(NewOrder);
}

void ACustomer::OccupyTable(ACustomerTable* Table)
{
	SetTargetTable(Table);
}

ACustomerTable* ACustomer::OccupiedTable() const
{
	return GetTargetTable();
}

void ACustomer::EndMoveToCachRegister()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	ACustomerState* CustomerState = Cast<ACustomerState>(StateAIController->GetAIState());
	check(CustomerState);

	GenerateOrder();

	CustomerState->SetCurrentState(ECustomerState::MoveToTable);
}

void ACustomer::EndMoveToTable()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	ACustomerState* CustomerState = Cast<ACustomerState>(StateAIController->GetAIState());
	check(CustomerState);

	CustomerState->SetCurrentState(ECustomerState::Eating);
}

void ACustomer::EndEating()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	ACustomerState* CustomerState = Cast<ACustomerState>(StateAIController->GetAIState());
	check(CustomerState);

	CustomerState->SetCurrentState(ECustomerState::Exiting);
}

void ACustomer::EndExiting()
{
	UCustomerTableSubsystem* CustomerTableSubsystem = GetWorld()->GetSubsystem<UCustomerTableSubsystem>();
	CustomerTableSubsystem->UnoccupiedTable(this);
	GetWorld()->DestroyActor(this);
}

