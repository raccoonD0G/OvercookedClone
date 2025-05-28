// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CashRegister.h"
#include "Interfaces/TakeOrderInterface.h"
#include "Actors/FinishStation.h"
#include "Net/UnrealNetwork.h"


ACashRegister::ACashRegister()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void ACashRegister::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACashRegister, Orders);
}

void ACashRegister::Interact(AActor* Caller)
{
	Super::Interact(Caller);

	if (!Caller || !Caller->GetClass()->ImplementsInterface(UTakeOrderInterface::StaticClass()))
	{
		return;
	}

	if (!FinishStation) return;

	if (Orders.Num() == 0) return;

	ITakeOrderInterface::Execute_SetCurrentRecipe(Caller, this, Orders[0]);
}

void ACashRegister::AddOrder(FOrder Order)
{
	if (HasAuthority())
	{
		Orders.Add(Order);
	}
}

void ACashRegister::DeleteOrder()
{
	if (HasAuthority())
	{
		Orders.RemoveAt(0);
	}
}