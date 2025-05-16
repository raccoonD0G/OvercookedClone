// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Order.h"
#include "Customer.generated.h"

UCLASS()
class OVERCOOKEDCLONE_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomer();
	
public:
	FOrder GenerateOrder();
};
