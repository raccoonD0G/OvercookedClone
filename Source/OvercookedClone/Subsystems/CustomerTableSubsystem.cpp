// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CustomerTableSubsystem.h"
#include "Actors/CustomerTable.h"
#include "EngineUtils.h"

void UCustomerTableSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// 레벨에 존재하는 모든 ACustomerTable 찾아서 등록
	for (TActorIterator<ACustomerTable> It(&InWorld); It; ++It)
	{
		ACustomerTable* Table = *It;
		if (IsValid(Table))
		{
			NotOccupiedTables.Add(Table);
		}
	}
}

ACustomerTable* UCustomerTableSubsystem::GetNotOccupiedTable()
{
	if (NotOccupiedTables.Num() == 0)
	{
		return nullptr;
	}

	// TSet을 배열로 변환하여 인덱스로 접근
	TArray<TObjectPtr<ACustomerTable>> TableArray = NotOccupiedTables.Array();
	int32 RandomIndex = FMath::RandRange(0, TableArray.Num() - 1);

	ACustomerTable* ChosenTable = TableArray[RandomIndex];

	// 집합 업데이트
	NotOccupiedTables.Remove(ChosenTable);
	OccupiedTables.Add(ChosenTable);

	return ChosenTable;
}