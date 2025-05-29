// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimerComponent.h"
#include "Net/UnrealNetwork.h"


UTimerComponent::UTimerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TimeLeft = MaxTimeLeft;
	SetIsReplicated(true);
}

void UTimerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTimerComponent, TimeLeft);
}

void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();
	TimeLeft = MaxTimeLeft;
}

void UTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeLeft -= DeltaTime;
	if (TimeLeft < 0)
	{
		OnTimerFinish.Broadcast();
	}
}