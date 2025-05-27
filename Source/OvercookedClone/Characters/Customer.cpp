// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Customer.h"
#include "Actors/CashRegister.h"
#include "UObject/EnumProperty.h"

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
	NewOrder.RecipeType = static_cast<ERecipeType>(FMath::RandRange(0, EnumPtr->NumEnums() - 1));
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

