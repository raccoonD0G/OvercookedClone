// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamBulidingWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API UTeamBulidingWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> GameStartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> PlayerCountText;
	
};
