// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/StateAIPawn.h"
#include "Net/UnrealNetwork.h"


AStateAIPawn::AStateAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AStateAIPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AStateAIPawn, AIState);
}

AAIState* AStateAIPawn::GetAIState() const
{
	return AIState;
}

void AStateAIPawn::SetAIState(AAIState* NewAIState)
{
	AIState = NewAIState;
}
