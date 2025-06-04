// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/StateAICharacter.h"
#include "Mouse.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API AMouse : public AStateAICharacter
{
	GENERATED_BODY()
	
public:
	AMouse();
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInteractComponent> InteractComponent;
	

	UFUNCTION()
	void Interact(AActor* Caller);
};
