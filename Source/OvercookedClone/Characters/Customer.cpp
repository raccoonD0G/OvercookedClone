// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Customer.h"
#include "Actors/CashRegister.h"
#include "UObject/EnumProperty.h"
#include "Subsystems/CustomerTableSubsystem.h"
#include "AIController/StateAIController.h"
#include "AIStates/CustomerState.h"
#include "Actors/CustomerTable.h"
#include "GameStates/KitchenGameState.h"

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();
	ExitPos = GetActorLocation();
}

void ACustomer::Init(ACashRegister* NewCashRegister)
{
	SetCashRegister(NewCashRegister);
}

void ACustomer::GenerateOrder()
{
	check(TargetTable);
	FOrder NewOrder;
	NewOrder.CustomerTable = TargetTable;
	UEnum* EnumPtr = StaticEnum<ERecipeType>();
	NewOrder.RecipeType = static_cast<ERecipeType>(FMath::RandRange(1, EnumPtr->NumEnums() - 2));
	CashRegister->AddOrder(NewOrder);
}

void ACustomer::OccupyTable(ACustomerTable* Table)
{
	SetTargetTable(Table);
	TargetTable->OnFoodPlaced.AddDynamic(this, &ACustomer::EndWaitingForFood);
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

	UCustomerTableSubsystem* TableSubsystem = GetWorld()->GetSubsystem<UCustomerTableSubsystem>();
	check(TableSubsystem);

	if (TableSubsystem->LeftSeatsNum() == 0)
	{
		AKitchenGameState* KitchenGameState = GetWorld()->GetGameState<AKitchenGameState>();
		if (KitchenGameState)
		{
			KitchenGameState->SetIsSeatsFullTrue();
		}

		CustomerState->SetCurrentState(ECustomerState::Exiting);
		return;
	}

	TableSubsystem->OccupyTable(this);

	GenerateOrder();

	CustomerState->SetCurrentState(ECustomerState::MoveToTable);
}

void ACustomer::EndMoveToTable()
{
	AStateAIController* StateAIController = Cast<AStateAIController>(GetController());
	check(StateAIController);
	ACustomerState* CustomerState = Cast<ACustomerState>(StateAIController->GetAIState());
	check(CustomerState);

	CustomerState->SetCurrentState(ECustomerState::WaitForFood);
}

void ACustomer::EndWaitingForFood()
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
	UCustomerTableSubsystem* CustomerTableSubsystem = GetWorld()->GetSubsystem<UCustomerTableSubsystem>();
	check(CustomerTableSubsystem);

	CustomerTableSubsystem->UnoccupiedTable(this);

	AKitchenGameState* KitchenGameState = GetWorld()->GetGameState<AKitchenGameState>();
	if (KitchenGameState)
	{
		if (KitchenGameState->GetIsSeatsFull())
		{
			KitchenGameState->SetIsSeatsFullFalse();
		}
	}

	CustomerState->SetCurrentState(ECustomerState::Exiting);
}

void ACustomer::EndExiting()
{
	GetWorld()->DestroyActor(this);
}

