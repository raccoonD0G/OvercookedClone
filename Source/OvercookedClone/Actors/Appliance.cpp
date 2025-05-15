// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Appliance.h"
#include "Interfaces/ChangeIngredientStateInterface.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"

AAppliance::AAppliance()
{
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ�� ����� �ڽ� ������Ʈ ����
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	// �ؽ�Ʈ ���� ������Ʈ ���� �� �ڽ��� ����
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextComponent->SetupAttachment(BoxComponent);

	// �� ������ Ŭ���� �̸��� �ؽ�Ʈ�� ����
	FString ClassName = GetClass()->GetName();
	TextComponent->SetText(FText::FromString(ClassName));

	// ��Ʈ �� �ؽ�Ʈ ���� �� ����(Optional)
	TextComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextComponent->SetWorldSize(50.f);
}

void AAppliance::Interact_Implementation(AActor* Caller)
{
	if (!Caller || !Caller->GetClass()->ImplementsInterface(UChangeIngredientStateInterface::StaticClass()))
	{
		return;
	}

	IChangeIngredientStateInterface::Execute_ChangeIngredientState(Caller, OutIngredientState);
	
}


