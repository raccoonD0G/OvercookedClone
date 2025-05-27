// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_WaitWithCallback.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OVERCOOKEDCLONE_API UBTTask_WaitWithCallback : public UBTTask_Wait
{
	GENERATED_BODY()

public:
	UBTTask_WaitWithCallback();

protected:
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UFUNCTION(BlueprintNativeEvent, Category = "AI")
	void OnWaitFinished(UBehaviorTreeComponent* OwnerComp);
	virtual void OnWaitFinished_Implementation(UBehaviorTreeComponent* OwnerComp);
};
