// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Recipe.h"
#include "Interfaces/InteractableInterface.h"
#include "Appliance.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API AAppliance : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AAppliance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UTextRenderComponent> TextComponent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EIngredientState OutIngredientState;

public:
	virtual void Interact_Implementation(AActor* Caller) override;

};
