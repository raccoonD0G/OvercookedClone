// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_SetRandomPos.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetRandomPos::UBTTask_SetRandomPos()
{
	NodeName = TEXT("Set Random Position");

	SearchRadius = 500.0f;
}

EBTNodeResult::Type UBTTask_SetRandomPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = AIPawn->GetActorLocation();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (!NavSys)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation RandomLocation;

	if (NavSys->GetRandomReachablePointInRadius(Origin, SearchRadius, RandomLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPos"), RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
