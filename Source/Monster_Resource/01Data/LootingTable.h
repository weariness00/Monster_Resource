// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LootingTable.generated.h"

USTRUCT()
struct FDropItem
{
	GENERATED_BODY()

public:
	FDropItem() : itemId(-1), dropCount(0){};
	FDropItem(int id, uint8 count) : itemId(id), dropCount(count) { };

	UPROPERTY(VisibleAnywhere)
	int itemId;

	UPROPERTY(VisibleAnywhere)
	uint8 dropCount;
};

USTRUCT()
struct FLootingItem
{
	GENERATED_BODY()

public:
	FLootingItem() : itemId(-1), minDropCount(0), maxDropCount(1), probability(1.0f) {};

	UPROPERTY(EditDefaultsOnly)
	int itemId;
	UPROPERTY(EditDefaultsOnly)
	uint8 minDropCount;
	UPROPERTY(EditDefaultsOnly)
	uint8 maxDropCount;
	UPROPERTY(EditDefaultsOnly)
	float probability;

	bool IsDrop() const
	{
		return probability >= FMath::FRandRange(0.0f, 1.0f);
	}

	uint8 GetDropCount() const
	{
		return FMath::RandRange(minDropCount, maxDropCount);
	}
};

USTRUCT()
struct FDTLootingTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	FDTLootingTable() : targetID(-1){};

	TArray<FDropItem> Looting() const
	{
		TArray<FDropItem> dropItems;

		for (FLootingItem lootingItem : lootingItems)
		{
			if(lootingItem.IsDrop())
			{
				dropItems.Add({ lootingItem.itemId, lootingItem.GetDropCount() });
			}
		}

		return dropItems;
	}

public:
	UPROPERTY(EditDefaultsOnly)
		int targetID;
	UPROPERTY(EditDefaultsOnly)
		TArray<FLootingItem> lootingItems;
};
