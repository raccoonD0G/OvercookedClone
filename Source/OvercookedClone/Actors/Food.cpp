// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Food.h"


AFood::AFood()
{
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponent ����
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// ��Ʈ ������Ʈ�� ����
	RootComponent = MeshComponent;
}

