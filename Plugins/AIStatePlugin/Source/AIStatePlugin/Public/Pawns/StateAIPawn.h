// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/StateAIInterface.h"
#include "StateAIPawn.generated.h"

UCLASS()
class AISTATEPLUGIN_API AStateAIPawn : public APawn, public IStateAIInterface
{
	GENERATED_BODY()

public:
	AStateAIPawn();
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	virtual class AAIState* GetAIState() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetAIState(class AAIState* NewAIState) override;

private:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AAIState> AIState;
};
