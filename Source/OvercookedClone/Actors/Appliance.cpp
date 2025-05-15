// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Appliance.h"
#include "Interfaces/ChangeIngredientStateInterface.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"

AAppliance::AAppliance()
{
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트로 사용할 박스 컴포넌트 생성
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	// 텍스트 렌더 컴포넌트 생성 및 박스에 부착
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextComponent->SetupAttachment(BoxComponent);

	// 이 액터의 클래스 이름을 텍스트로 설정
	FString ClassName = GetClass()->GetName();
	TextComponent->SetText(FText::FromString(ClassName));

	// 폰트 및 텍스트 정렬 등 설정(Optional)
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


