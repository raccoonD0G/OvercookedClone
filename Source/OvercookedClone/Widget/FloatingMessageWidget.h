// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ActorOwnableUserWidget.h"
#include "FloatingMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERCOOKEDCLONE_API UFloatingMessageWidget : public UActorOwnableUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void Start();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MessageText;

private:
	float ElapsedTime;

	UPROPERTY(EditAnywhere)
	float TotalLifetime;

	FVector2D StartPosition;
};
