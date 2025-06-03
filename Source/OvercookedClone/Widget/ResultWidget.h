// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OpenEntryLevel();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ResultScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BackToMainButton;

	UFUNCTION()
	void SetResultScoreText(float Score);


};
