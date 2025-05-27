// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/StateAIController.h"
#include "AIState/AIState.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AStateAIController::AStateAIController()
{
	AIStateClass = AAIState::StaticClass();
}

void AStateAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
	{
		if (AIState == nullptr && AIStateClass != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AIState = GetWorld()->SpawnActor<AAIState>(AIStateClass, SpawnParams);
			check(AIState);
		}
	}
}

void AStateAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (HasAuthority())
	{
		RunAI();
	}
}

void AStateAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AStateAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

