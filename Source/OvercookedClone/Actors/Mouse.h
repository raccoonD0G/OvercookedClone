// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableBase.h"
#include "Mouse.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API AMouse : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	AMouse();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Interact(AActor* Caller) override;
};
