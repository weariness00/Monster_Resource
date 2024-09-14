// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../00Game/ActorBase.h"
#include "ItemBase.generated.h"

struct FDTItemDataTable;

/**
 * 
 */
UCLASS()
class MONSTER_RESOURCE_API AItemBase : public AActorBase
{
	GENERATED_BODY()
public:
	AItemBase();
	~AItemBase();

// Getter Setter �Լ���
public:
	int32 GetId() { return id; }
	void SetId(int32 value) { id = value; }

protected:
	UPROPERTY(EditInstanceOnly)
		int32 id;
	UPROPERTY(EditAnywhere)
		uint16 stack; // �� ������ �ִ� ����
	UPROPERTY(EditAnywhere)
		uint16 count; // ������ ����

	FDTItemDataTable* data;
};
