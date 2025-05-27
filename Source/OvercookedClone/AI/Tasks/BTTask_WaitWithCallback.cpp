// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_WaitWithCallback.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_WaitWithCallback::UBTTask_WaitWithCallback()
{
	NodeName = "Wait With Callback";
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

void UBTTask_WaitWithCallback::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	if (TaskResult == EBTNodeResult::Succeeded)
	{
		OnWaitFinished(&OwnerComp);
	}
}

void UBTTask_WaitWithCallback::OnWaitFinished_Implementation(UBehaviorTreeComponent* OwnerComp)
{
	
}
