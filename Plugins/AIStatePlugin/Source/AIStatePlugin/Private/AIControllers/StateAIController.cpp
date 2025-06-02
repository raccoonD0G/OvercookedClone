// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllers/StateAIController.h"
#include "AIStates/AIState.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/StateAIInterface.h"

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
		IStateAIInterface* StateAIInterface = Cast<IStateAIInterface>(InPawn);
		if (StateAIInterface)
		{
			StateAIInterface->SetAIState(AIState);
		}

		RunAI();
	}
}

void AStateAIController::BeginDestroy()
{
	Super::BeginDestroy();

	if (AIState)
	{
		if (GetWorld())
		{
			GetWorld()->DestroyActor(AIState);
			AIState = nullptr;
		}
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

