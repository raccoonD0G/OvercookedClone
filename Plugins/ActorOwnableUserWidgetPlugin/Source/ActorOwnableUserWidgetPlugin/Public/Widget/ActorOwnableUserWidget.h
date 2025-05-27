// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorOwnableUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTOROWNABLEUSERWIDGETPLUGIN_API UActorOwnableUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> OwningActor;
};
