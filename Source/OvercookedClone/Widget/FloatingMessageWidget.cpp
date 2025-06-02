// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FloatingMessageWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

void UFloatingMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ElapsedTime = 0.0f;
	TotalLifetime = 1.0f;

	if (MessageText->Slot)
	{
		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(MessageText->Slot))
		{
			StartPosition = CanvasPanelSlot->GetPosition();
		}
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UFloatingMessageWidget::Start()
{
	SetRenderOpacity(1.0f);
	ElapsedTime = 0.0f;
	SetVisibility(ESlateVisibility::Visible);

	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(MessageText->Slot);
	if (!CanvasPanelSlot) return;
	CanvasPanelSlot->SetPosition(StartPosition);
}

void UFloatingMessageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetVisibility() != ESlateVisibility::Visible) return;

	if (!(MessageText && MessageText->Slot)) return;

	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(MessageText->Slot);
	if (!CanvasPanelSlot) return;

	ElapsedTime += InDeltaTime;
	float Alpha = ElapsedTime / TotalLifetime;

	FVector2D NewPosition = StartPosition + FVector2D(0, -50.0f * Alpha);
	CanvasPanelSlot->SetPosition(NewPosition);

	SetRenderOpacity(FMath::Lerp(1.0f, 0.0f, Alpha));

	if (ElapsedTime >= TotalLifetime)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
