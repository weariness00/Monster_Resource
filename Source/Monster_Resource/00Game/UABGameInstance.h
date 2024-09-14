// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "UABGameInstance.generated.h"

struct FDTItemDataTable;
struct FDTLootingTable;
struct FDTProductionTable;

UCLASS()
class MONSTER_RESOURCE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UABGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

private:
	static bool GenerateDataTable(const FString& path, UDataTable*& table);
	
public:
	FDTItemDataTable* GetItemData(int32 id) const;
	FDTLootingTable* GetLootingTable(int targetID) const;
	FDTProductionTable* GetProductionTable(const int productId) const;

private:
	UDataTable* itemTable;
	TMap<int, FDTProductionTable*> ProductionTable;
	TMap<int, FDTLootingTable*> LootingTable;
};
