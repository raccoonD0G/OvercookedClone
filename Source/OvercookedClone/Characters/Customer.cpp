// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Customer.h"


// Sets default values
ACustomer::ACustomer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FOrder ACustomer::GenerateOrder()
{
	return FOrder();
}

