// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Ingredient.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

AIngredient::AIngredient()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SceneComponent"));
    RootComponent = SceneComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
    TextComponent->SetupAttachment(RootComponent);

    // 클래스 이름을 텍스트로 설정
    FString ClassName = GetClass()->GetName();
    ClassName.RemoveFromStart(TEXT("BP_"));
    ClassName.RemoveFromEnd(TEXT("_C"));

    TextComponent->SetText(FText::FromString(ClassName));

    // 텍스트 위치 조정
    TextComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
    TextComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    TextComponent->SetWorldSize(50.f);

    bReplicates = true;
}

void AIngredient::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AIngredient, IngredientState);
}

void AIngredient::Server_SetIngredientState_Implementation(EIngredientState NewIngredientState)
{
    IngredientState = NewIngredientState;
}
