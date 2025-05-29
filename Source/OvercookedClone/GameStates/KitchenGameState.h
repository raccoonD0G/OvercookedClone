// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KitchenGameState.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API AKitchenGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AKitchenGameState();

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void IncreaseMouseCount() { MouseCount++; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void DecreaseMouseCount() { MouseCount--; }

	FORCEINLINE int32 GetMouseCount() const { return MouseCount; }

	FORCEINLINE void SetIsSeatsFullTrue() { bIsSeatsFull = true; }
	FORCEINLINE void SetIsSeatsFullFalse() { bIsSeatsFull = false; }

	FORCEINLINE bool GetIsSeatsFull() const { return bIsSeatsFull; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetScore() const { return Score; }
	
private:
	UPROPERTY(Replicated, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 MouseCount;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float MouseCountRatio;

	UPROPERTY(Replicated, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	uint8 bIsSeatsFull : 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float SeatsFullRatio;

	UPROPERTY(Replicated, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	float Score;
	
};
