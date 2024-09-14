// Fill out your copyright notice in the Description page of Project Settings.

#include "UABGameInstance.h"
#include "../01Data/ItemDataTable.h"
#include "../01Data/LootingTable.h"
#include "../01Data/ProductionTable.h"
#include "../03System/Production/CombinationMethod.h"

UABGameInstance::UABGameInstance()
{
	itemTable = nullptr;
	ProductionTable.Empty();
	LootingTable.Empty();
}

void UABGameInstance::Init()
{
	Super::Init();

	GenerateDataTable(TEXT("/Game/01Data/DT_Item"), itemTable);
	// 생산 테이블 초기화
	{
		UDataTable* table;
		GenerateDataTable(TEXT("/Game/01Data/DT_ProductionTable"), table);

		TArray<FDTProductionTable*> arr;
		table->GetAllRows<FDTProductionTable>(TEXT("GetAllRows"), arr);
		for (FDTProductionTable* data : arr)
		{
			ProductionTable.Add(data->productId, data);
		}
	}
	// 몬스터 루팅 테이블 초기화
	{
		UDataTable* table;
		GenerateDataTable(TEXT("/Game/01Data/DT_LootingTable"), table);

		TArray<FDTLootingTable*> arr;
		table->GetAllRows<FDTLootingTable>(TEXT("GetAllRows"), arr);
		for (FDTLootingTable* data : arr)
		{
			LootingTable.Add(data->targetID, data);
		}
	}
}

void UABGameInstance::Shutdown()
{
	Super::Shutdown();

	ACombinationMethod::StaticClear();
}

bool UABGameInstance::GenerateDataTable(const FString& path, UDataTable*& table)
{
	table = LoadObject<UDataTable>(nullptr, *path);
	if (table)
	{
		UE_LOG(LogTemp, Log, TEXT("%s\nData Table Load Success"), *path);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s\nData Table Load Failed"), *path);
	}

	return table != nullptr;
}

FDTItemDataTable* UABGameInstance::GetItemData(int32 id) const
{
	return itemTable->FindRow<FDTItemDataTable>(*FString::FromInt(id), TEXT(""));
}

FDTLootingTable* UABGameInstance::GetLootingTable(int targetID) const
{
	return LootingTable.Contains(targetID) ? LootingTable[targetID] : nullptr;
}

FDTProductionTable* UABGameInstance::GetProductionTable(const int productId) const
{
	return ProductionTable.Contains(productId) ? ProductionTable[productId] : nullptr;
}
