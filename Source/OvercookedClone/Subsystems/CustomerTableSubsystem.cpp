// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CustomerTableSubsystem.h"
#include "Actors/CustomerTable.h"
#include "EngineUtils.h"

void UCustomerTableSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// ������ �����ϴ� ��� ACustomerTable ã�Ƽ� ���
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

	// TSet�� �迭�� ��ȯ�Ͽ� �ε����� ����
	TArray<TObjectPtr<ACustomerTable>> TableArray = NotOccupiedTables.Array();
	int32 RandomIndex = FMath::RandRange(0, TableArray.Num() - 1);

	ACustomerTable* ChosenTable = TableArray[RandomIndex];

	// ���� ������Ʈ
	NotOccupiedTables.Remove(ChosenTable);
	OccupiedTables.Add(ChosenTable);

	return ChosenTable;
}