// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTTask_MoveToWithCallback.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OVERCOOKEDCLONE_API UBTTask_MoveToWithCallback : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_MoveToWithCallback();

	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	void OnMoveSuccess(UBehaviorTreeComponent* OwnerComp);
	virtual void OnMoveSuccess_Implementation(UBehaviorTreeComponent* OwnerComp);
};