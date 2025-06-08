// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FinishStation.h"
#include "Actors/CustomerTable.h"
#include "Actors/Food.h"
#include "Interfaces/FinishStationInteractInterface.h"
#include "Actors/Ingredient.h"
#include "Subsystems/RecipeSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/KitchenHUD.h"
#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorOwnableWidgetComponent.h"
#include "Widget/FloatingMessageWidget.h"

AFinishStation::AFinishStation()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	SuccessWidgetComponent = CreateDefaultSubobject<UActorOwnableWidgetComponent>(TEXT("SuccessWidgetComponent"));
	SuccessWidgetComponent->SetupAttachment(RootComponent);

	FailWidgetComponent = CreateDefaultSubobject<UActorOwnableWidgetComponent>(TEXT("FailWidgetComponent"));
	FailWidgetComponent->SetupAttachment(RootComponent);
}

void AFinishStation::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFinishStation, CurrentOrder);
	DOREPLIFETIME(AFinishStation, IngredientInfos);
	DOREPLIFETIME(AFinishStation, FoodOnTable);
}

void AFinishStation::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetCurrentOrder(FOrder());
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		AKitchenHUD* KitchenHUD = Cast<AKitchenHUD>(PlayerController->GetHUD());
		if (KitchenHUD)
		{
			KitchenHUD->SetFinishStation(this);
		}
	}
}

bool AFinishStation::OnClicked()
{
	URecipeSubsystem* RecipeSubsystem = GetGameInstance()->GetSubsystem<URecipeSubsystem>();

	if (!RecipeSubsystem)
	{
		return false;
	}

	if (IngredientInfos.IsEmpty())
	{
		return false;
	}

	TArray<FIngredientInfo> IngredientRequirements = RecipeSubsystem->GetRecipeByType(CurrentOrder.RecipeType).RequiredIngredients;

	bool bIsCorrect = true;

	for (const auto& IngredientRequirement : IngredientRequirements)
	{
		if (!IngredientInfos.Contains(IngredientRequirement))
		{
			bIsCorrect = false;
		}
	}

	if (bIsCorrect)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AFood* NewFood = GetWorld()->SpawnActor<AFood>(FoodClasses[CurrentOrder.RecipeType], SpawnParam);
		OnCookSuccess.Broadcast(CurrentOrder);
		SetFoodOnTable(NewFood);
		FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		NewFood->AttachToComponent(MeshComponent, AttachmentTransformRules, TEXT("TableTop"));

		SetCurrentOrder(FOrder());
	}

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (AActor* Child : AttachedActors)
	{
		if (IsValid(Child) && Child->IsA<AIngredient>())
		{
			Child->Destroy();
		}
	}

	IngredientInfos.Empty();

	OnIngredientInfosChange.Broadcast(IngredientInfos);

	return bIsCorrect;
}

void AFinishStation::ShowSuccessWidget()
{
	UFloatingMessageWidget* SuccessWidget = Cast<UFloatingMessageWidget>(SuccessWidgetComponent->GetWidget());
	if (SuccessWidget)
	{
		SuccessWidget->Start();
	}
}

void AFinishStation::ShowFailWidget()
{
	UFloatingMessageWidget* FailWidget = Cast<UFloatingMessageWidget>(FailWidgetComponent->GetWidget());
	if (FailWidget)
	{
		FailWidget->Start();
	}
}

void AFinishStation::SetCurrentOrder(FOrder NewOrder)
{
	CurrentOrder = NewOrder;
	OnOrderSet.Broadcast(NewOrder);
}

void AFinishStation::AddIngredientInfo(FIngredientInfo IngredientInfo)
{
	if (HasAuthority())
	{
		IngredientInfos.Add(IngredientInfo);
		OnIngredientInfosChange.Broadcast(IngredientInfos);
	}
}

void AFinishStation::OnRep_CurrentOrder()
{
	OnOrderSet.Broadcast(CurrentOrder);
}

void AFinishStation::OnRep_Ingredients()
{
	OnIngredientInfosChange.Broadcast(IngredientInfos);
}

void AFinishStation::Interact(AActor* Caller)
{
	Super::Interact(Caller);

	if (!Caller || !Caller->GetClass()->ImplementsInterface(UFinishStationInteractInterface::StaticClass()))
	{
		return;
	}

	if (FoodOnTable)
	{
		return;
	}

	IFinishStationInteractInterface::Execute_PutOutIngredient(Caller, this);
}