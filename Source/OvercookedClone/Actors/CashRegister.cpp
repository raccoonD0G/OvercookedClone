// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CashRegister.h"
#include "Interfaces/TakeOrderInterface.h"
#include "Actors/FinishStation.h"


ACashRegister::ACashRegister()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACashRegister::Interact(AActor* Caller)
{
	if (!Caller || !Caller->GetClass()->ImplementsInterface(UTakeOrderInterface::StaticClass()))
	{
		return;
	}

	if (!FinishStation) return;

	if (Orders.Num() == 0) return;

	FinishStation->SetCurrentOrder(Orders[0]);
	ITakeOrderInterface::Execute_SetCurrentRecipe(Caller, Orders[0].RecipeType);
	DeleteOrder();
}

void ACashRegister::AddOrder(FOrder Order)
{
	Orders.Add(Order);
}

void ACashRegister::DeleteOrder()
{
	Orders.RemoveAt(0);
}