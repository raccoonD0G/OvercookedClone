// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToWithCallback.h"
#include "AIController.h"

UBTTask_MoveToWithCallback::UBTTask_MoveToWithCallback()
{
	NodeName = "Move To With Callback";
	bNotifyTick = false;
	bNotifyTaskFinished = true;
}

void UBTTask_MoveToWithCallback::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

    if (TaskResult == EBTNodeResult::Succeeded)
    {
		OnMoveSuccess(&OwnerComp);
    }
}

void UBTTask_MoveToWithCallback::OnMoveSuccess_Implementation(UBehaviorTreeComponent* OwnerComp)
{
}
