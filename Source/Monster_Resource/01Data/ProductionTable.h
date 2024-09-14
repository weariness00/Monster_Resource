// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ProductionTable.generated.h"

USTRUCT()
struct FDTProductionTable : public FTableRowBase
{
	GENERATED_BODY()

	FDTProductionTable() : productId(-1), productDuration(-1) {};

	UPROPERTY(EditDefaultsOnly)
		int productId;
	UPROPERTY(EditDefaultsOnly)
		// 몇초에 1번 생산하는지
		float productDuration; 
	UPROPERTY(EditDefaultsOnly)
		// Key : Item Id
		// Value : Item이 필요한 개수
		TMap<int32, uint16> needItems;
	UPROPERTY(EditDefaultsOnly)
		// Key : Item Id
		// Value : 생산될 Item의 개수
		TMap<int32, uint16> productItems;
};
