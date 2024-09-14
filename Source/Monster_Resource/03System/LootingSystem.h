// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../01Data/LootingTable.h"
#include "LootingSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTER_RESOURCE_API ULootingSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULootingSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 드랍할 아이템들을 결정
	void GenerateDropItems(int id);

protected:
	UPROPERTY(VisibleAnywhere)
		TArray<FDropItem> dropItems; // 드랍될 아이템들의 아이디들
};
