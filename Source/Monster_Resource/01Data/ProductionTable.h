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
		// ���ʿ� 1�� �����ϴ���
		float productDuration; 
	UPROPERTY(EditDefaultsOnly)
		// Key : Item Id
		// Value : Item�� �ʿ��� ����
		TMap<int32, uint16> needItems;
	UPROPERTY(EditDefaultsOnly)
		// Key : Item Id
		// Value : ����� Item�� ����
		TMap<int32, uint16> productItems;
};
