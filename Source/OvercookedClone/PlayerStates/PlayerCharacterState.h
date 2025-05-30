// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacterState.generated.h"

UENUM(BlueprintType)
enum class EPlayerTask : uint8
{
	TakeOrder,
	TakeIngredient,
	ChangeIngredientStateOrPutOnFinishTable,
	PutOnFinishTable
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNextTaskChangeDelegate, EPlayerTask, NewTask);

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
	FORCEINLINE EPlayerTask GetCurrentState() const { return NextTask; }

	UFUNCTION(BlueprintCallable)
	void SetNextTask(EPlayerTask NewTask);

private:
	UFUNCTION(Server, Reliable)
	void Server_SetNextTask(EPlayerTask NewTask);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerTask NextTask;

public:
	FOnNextTaskChangeDelegate OnNextTaskChange;

	UFUNCTION(BlueprintCallable)
	void EndTakeOrder();

	UFUNCTION(BlueprintCallable)
	void EndTakeIngredient();

	UFUNCTION(BlueprintCallable)
	void EndChangeIngredientState();

	UFUNCTION(BlueprintCallable)
	void EndPutOnFinishTable();

	UFUNCTION(BlueprintCallable)
	void EndClickFinishStation();
	
};
