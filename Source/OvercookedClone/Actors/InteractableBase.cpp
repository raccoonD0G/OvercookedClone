// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableBase.h"
#include "Components/InteractComponent.h"


AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

    InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
    InteractComponent->SetupAttachment(RootComponent);
}

void AInteractableBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    InteractComponent->OnInteract.AddDynamic(this, &AInteractableBase::Interact);
}

void AInteractableBase::Interact(AActor* Caller)
{

}