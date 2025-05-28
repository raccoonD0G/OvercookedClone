// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ActorOwnableUserWidget.h"
#include "FinishStationWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API UFinishStationWidget : public UActorOwnableUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnFinishStationClicked();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> FinishStationButton;
};
