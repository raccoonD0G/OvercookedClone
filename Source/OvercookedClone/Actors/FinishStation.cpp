// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FinishStation.h"
#include "Actors/CustomerTable.h"
#include "Actors/Food.h"
#include "Interfaces/FinishStationInteractInterface.h"
#include "Actors/Ingredient.h"
#include "Subsystems/RecipeSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/KitchenHUD.h"


AFinishStation::AFinishStation()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFinishStation::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnClicked.AddDynamic(this, &AFinishStation::OnActorClicked);

}

void AFinishStation::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (AKitchenHUD* KitchenHUD = Cast<AKitchenHUD>(PC->GetHUD()))
	{
		KitchenHUD->SetFinishStation(this);
	}
}


void AFinishStation::OnActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	URecipeSubsystem* RecipeSubsystem = GetGameInstance()->GetSubsystem<URecipeSubsystem>();

	if (!RecipeSubsystem) return;

	if (Ingredients.IsEmpty()) return;

	TArray<FIngredientInfo> IngredientRequirements = RecipeSubsystem->GetRecipeByType(CurrentOrder.RecipeType).RequiredIngredients;

	bool bIsCorrect = true;

	for (const auto& IngredientRequirement : IngredientRequirements)
	{
		if (!Ingredients.Contains(IngredientRequirement))
		{
			bIsCorrect = false;
		}
	}

	if (bIsCorrect)
	{
		AFood* NewFood = GetWorld()->SpawnActor<AFood>(FoodClasses[CurrentOrder.RecipeType]);
		CurrentOrder.CustomerTable->PlaceFood(NewFood);
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

	Ingredients.Empty();

	OnIngredientClear.Broadcast();
}

void AFinishStation::SetCurrentOrder(FOrder NewOrder)
{
	CurrentOrder = NewOrder;
	OnOrderSet.Broadcast(NewOrder);
}

void AFinishStation::Interact(AActor* Caller)
{
	if (!Caller || !Caller->GetClass()->ImplementsInterface(UFinishStationInteractInterface::StaticClass()))
	{
		return;
	}

	AIngredient* Ingredient = IFinishStationInteractInterface::Execute_PutOutIngredient(Caller);

	if (!Ingredient) return;

	OnIngredientAdd.Broadcast(Ingredient);

	Ingredients.Add(FIngredientInfo(Ingredient->GetIngredientType(), Ingredient->GetIngredientState()));

	Ingredient->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Ingredient->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}