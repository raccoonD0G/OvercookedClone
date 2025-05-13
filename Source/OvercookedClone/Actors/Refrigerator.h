// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "Refrigerator.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ARefrigerator : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
	ARefrigerator();

public:
	virtual void Interact_Implementation(AActor* Caller) override;
	
};
