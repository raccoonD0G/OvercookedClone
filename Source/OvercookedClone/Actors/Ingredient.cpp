// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Ingredient.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AIngredient::AIngredient()
{
	PrimaryActorTick.bCanEverTick = true;

    // 루트 컴포넌트로 사용할 박스 컴포넌트 생성
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // 텍스트 렌더 컴포넌트 생성 및 박스에 부착
    TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
    TextComponent->SetupAttachment(BoxComponent);

    // 클래스 이름을 텍스트로 설정
    FString ClassName = GetClass()->GetName();
    TextComponent->SetText(FText::FromString(ClassName));

    // 텍스트 위치 조정 (박스 위에 띄우기)
    TextComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
    TextComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    TextComponent->SetWorldSize(50.f);
}

void AIngredient::ChangeIngredientState(EIngredientState NewIngredientState)
{
    if (IngredientState != EIngredientState::Raw) return;
    IngredientState = NewIngredientState;
}
