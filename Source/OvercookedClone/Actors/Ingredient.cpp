// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Ingredient.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AIngredient::AIngredient()
{
	PrimaryActorTick.bCanEverTick = true;

    // ��Ʈ ������Ʈ�� ����� �ڽ� ������Ʈ ����
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // �ؽ�Ʈ ���� ������Ʈ ���� �� �ڽ��� ����
    TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
    TextComponent->SetupAttachment(BoxComponent);

    // Ŭ���� �̸��� �ؽ�Ʈ�� ����
    FString ClassName = GetClass()->GetName();
    TextComponent->SetText(FText::FromString(ClassName));

    // �ؽ�Ʈ ��ġ ���� (�ڽ� ���� ����)
    TextComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
    TextComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    TextComponent->SetWorldSize(50.f);
}

void AIngredient::ChangeIngredientState(EIngredientState NewIngredientState)
{
    if (IngredientState != EIngredientState::Raw) return;
    IngredientState = NewIngredientState;
}
