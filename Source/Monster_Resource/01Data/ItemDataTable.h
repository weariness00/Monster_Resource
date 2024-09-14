// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ItemDataTable.generated.h"

USTRUCT(BlueprintType)
struct FDTItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FDTItemDataTable() : Name("Unknown"), Id(-1), Tear(-1), Explain("Empty"){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
		int32 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
		int32 Tear;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
		FString Explain;

	FDTItemDataTable& operator=(const FDTItemDataTable& data)
	{
		Name = data.Name;
		Id = data.Id;
		Tear = data.Tear;
		Explain = data.Explain;
		
		return *this;
	}
};

