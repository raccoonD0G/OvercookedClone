// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableBase.h"
#include "Components/InteractComponent.h"
#include "Components/ActorOwnableWidgetComponent.h"
#include "PlayerStates/PlayerCharacterState.h"
#include "Kismet/GameplayStatics.h"


AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

    USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

    InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));
    InteractComponent->SetupAttachment(RootComponent);

    InteractWidgetComponent = CreateDefaultSubobject<UActorOwnableWidgetComponent>(TEXT("InteractWidgetComponent"));
    InteractWidgetComponent->SetupAttachment(RootComponent);

    static ConstructorHelpers::FClassFinder<UUserWidget> InteractWidgetClassRef(TEXT("/Game/Widget/WBP_InteractWidget.WBP_InteractWidget_C"));
    if (InteractWidgetClassRef.Succeeded())
    {
        InteractWidgetComponent->SetWidgetClass(InteractWidgetClassRef.Class);
    }

    InteractWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AInteractableBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    InteractComponent->OnInteract.AddDynamic(this, &AInteractableBase::Interact);
}

void AInteractableBase::BeginPlay()
{
    Super::BeginPlay();
    if (GetNetMode() == ENetMode::NM_Client || GetNetMode() == ENetMode::NM_ListenServer || GetNetMode() == ENetMode::NM_Standalone)
    {
        BindCheckAndSetInteractWidget();
    }
}

void AInteractableBase::Interact(AActor* Caller)
{

}

void AInteractableBase::CheckAndSetInteractWidget(EPlayerTask NewState)
{
    if (InteractablePlayerStates.Contains(NewState))
    {
        InteractWidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        InteractWidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AInteractableBase::BindCheckAndSetInteractWidget()
{
    APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (APlayerCharacterState* PlayerCharacterState = Controller->GetPlayerState<APlayerCharacterState>())
    {
        PlayerCharacterState->OnNextTaskChange.AddDynamic(this, &AInteractableBase::CheckAndSetInteractWidget);
        CheckAndSetInteractWidget(PlayerCharacterState->GetNextTask());
    }
    else
    {
        // PlayerState가 아직 레플리케이트 안된 경우 -> 0.1초 후 재시도
        GetWorldTimerManager().SetTimer(RetryBindHandle, this, &AInteractableBase::BindCheckAndSetInteractWidget, 0.1f, false);
    }
}
