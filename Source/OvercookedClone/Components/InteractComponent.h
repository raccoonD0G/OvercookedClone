// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InteractComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractDelegate, AActor*, Caller);

UCLASS()
class OVERCOOKEDCLONE_API UInteractComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UInteractComponent();

public:
	FOnInteractDelegate OnInteract;

	UFUNCTION(BlueprintCallable)
	virtual void Interact(AActor* Caller);

	UFUNCTION()
	void ShowInteractWidget();

	UFUNCTION()
	void CloseInteractWidget();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UActorOwnableWidgetComponent> ActorOwnableWidgetComponent;
	
};
