// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food.h"


AFood::AFood()
{
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent 생성
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// 루트 컴포넌트로 설정
	RootComponent = MeshComponent;
}

