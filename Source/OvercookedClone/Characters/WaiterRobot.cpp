// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WaiterRobot.h"


// Sets default values
AWaiterRobot::AWaiterRobot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWaiterRobot::PlaceFood(AFood* Food)
{
	//FoodOnTable = Food;
	//FoodOnTable->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("TableTop"));
	//OnFoodPlaced.Broadcast();
}

void AWaiterRobot::ClearFood()
{
	/*if (FoodOnTable)
	{
		FoodOnTable->Destroy();
		FoodOnTable = nullptr;
	}*/
}

// Called when the game starts or when spawned
void AWaiterRobot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaiterRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWaiterRobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

