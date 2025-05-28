// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MouseSpawner.h"
#include "NavigationSystem.h"

AMouseSpawner::AMouseSpawner()
{
	SpawnRadius = 1000.0f;
}

AActor* AMouseSpawner::SpawnActorDeffered()
{
	AActor* SpawnedActor = Super::SpawnActorDeffered();

	FTransform RandomTransform = GetRandomNavMeshTransform(SpawnRadius);

	SpawnLocation = RandomTransform.GetLocation();
	SpawnRotation = RandomTransform.GetRotation().Rotator();

	SpawnedActor->SetActorTransform(RandomTransform);

	return SpawnedActor;
}

FTransform AMouseSpawner::GetRandomNavMeshTransform(float Radius)
{
	FNavLocation RandomNavLocation;
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	// 기본 위치에서 탐색
	if (NavSystem && NavSystem->GetRandomPointInNavigableRadius(SpawnCenterLocation, Radius, RandomNavLocation))
	{
		// 랜덤 회전 생성
		float RandomYaw = FMath::FRandRange(0.f, 360.f);
		FRotator YawOnlyRotation(0.f, RandomYaw, 0.f);
		return FTransform(YawOnlyRotation, RandomNavLocation.Location);
	}

	// 실패하면 기본 위치로 반환
	return FTransform(SpawnCenterRotation, SpawnCenterLocation);
}
