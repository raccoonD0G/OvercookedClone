// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStates/PlayerCharacterState.h"
#include "InteractableBase.generated.h"

UCLASS(Abstract, BlueprintType)
class OVERCOOKEDCLONE_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:
	AInteractableBase();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void Interact(AActor* Caller);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInteractComponent> InteractComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UActorOwnableWidgetComponent> InteractWidgetComponent;

	UPROPERTY(EditAnywhere)
	TSet<EPlayerTask> InteractablePlayerStates;

	UFUNCTION()
	void CheckAndSetInteractWidget(EPlayerTask NewState);

	void BindCheckAndSetInteractWidget();

	FTimerHandle RetryBindHandle;
};
