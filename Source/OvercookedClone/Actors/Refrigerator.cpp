// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Refrigerator.h"
#include "Interfaces/RefrigeratorInteractInterface.h"
#include "Actors/Ingredient.h"


ARefrigerator::ARefrigerator()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARefrigerator::Interact_Implementation(AActor* Caller)
{
	if (!Caller || !Caller->GetClass()->ImplementsInterface(URefrigeratorInteractInterface::StaticClass()))
	{
		return;
	}

	// �ʿ��� ������ �������̽����� �޾ƿ���
	TArray<EIngredientType> NecessaryIngredients;
	NecessaryIngredients = IRefrigeratorInteractInterface::Execute_GetNecessaryIngredients(Caller);

	if (NecessaryIngredients.Num() == 0)
	{
		return;
	}

	// �������� ��� ����
	int32 RandomIndex = FMath::RandRange(0, NecessaryIngredients.Num() - 1);
	EIngredientType SelectedIngredientType = NecessaryIngredients[RandomIndex];

	check(IngredientClasses[SelectedIngredientType]);

	FActorSpawnParameters IngredientSpawnParam;
	IngredientSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AIngredient* SelectedIngredientActor = GetWorld()->SpawnActor<AIngredient>(IngredientClasses[SelectedIngredientType], IngredientSpawnParam);

	check(SelectedIngredientActor);

	// ObtainIngredients ȣ��
	IRefrigeratorInteractInterface::Execute_ObtainIngredients(Caller, this, SelectedIngredientActor);
}


