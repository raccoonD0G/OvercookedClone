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


AFinishStation::AFinishStation()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void AFinishStation::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFinishStation, CurrentOrder);
	DOREPLIFETIME(AFinishStation, IngredientInfos);
}

void AFinishStation::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetCurrentOrder(FOrder());
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		AKitchenHUD* KitchenHUD = Cast<AKitchenHUD>(PC->GetHUD());
		if (KitchenHUD)
		{
			KitchenHUD->SetFinishStation(this);
		}
	}
}

void AFinishStation::OnClicked()
{
	URecipeSubsystem* RecipeSubsystem = GetGameInstance()->GetSubsystem<URecipeSubsystem>();

	if (!RecipeSubsystem) return;

	if (IngredientInfos.IsEmpty()) return;

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
		AFood* NewFood = GetWorld()->SpawnActor<AFood>(FoodClasses[CurrentOrder.RecipeType]);
		CurrentOrder.CustomerTable->PlaceFood(NewFood);
		SetCurrentOrder(FOrder());
	}

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (AActor* Child : AttachedActors)
	{
		if (IsValid(Child))
		{
			Child->Destroy();
		}
	}

	IngredientInfos.Empty();

	OnIngredientInfosChange.Broadcast(IngredientInfos);
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

	IFinishStationInteractInterface::Execute_PutOutIngredient(Caller, this);
}