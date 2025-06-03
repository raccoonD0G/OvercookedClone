// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ResultGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChange, float, NewScore);
/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AResultGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;
	virtual void PostInitializeComponents() override;

public:
	FOnScoreChange OnScoreChange;

	FORCEINLINE float GetScore() const { return Score; }

private:
	UPROPERTY(ReplicatedUsing = OnRep_Score)
	float Score;

private:
	UFUNCTION()
	void OnRep_Score();
	
};
