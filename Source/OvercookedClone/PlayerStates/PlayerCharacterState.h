// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacterState.generated.h"

UENUM(BlueprintType)
enum class EPlayerCharacterState : uint8
{
	TakeOrder,
	TakeIngredient,
	ChangeIngredientState,
	PutOnFinishTable
};
/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API APlayerCharacterState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APlayerCharacterState();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerCharacterState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EPlayerCharacterState NewState);

private:
	UFUNCTION(Server, Reliable)
	void Server_SetCurrentState(EPlayerCharacterState NewState);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerCharacterState CurrentState;
	
};
