// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster_Resource/00Game/ActorBase.h"
#include "CombinationMethod.generated.h"

class UABGameInstance;
class UFuelRequired;

USTRUCT()
struct FNeedCount {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	uint16 needItem; // 필요한 아이템 개수
	UPROPERTY(EditAnywhere)
	uint16 currentItem; // 현재 소유한 아이템 개수
};

USTRUCT()
struct FProductCount
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	uint16 productItem; // 생산될 아이템 개수
	UPROPERTY(EditAnywhere)
	uint16 currentItem; // 생산된 아이템 개수
};

// 조합법
UCLASS()
class MONSTER_RESOURCE_API ACombinationMethod : public AActorBase
{
	GENERATED_BODY()

public:
	static void StaticClear();

private:
	static UABGameInstance* gameInstance;
	static FTimerManager* timerManager;

public:	
	// Sets default values for this component's properties
	ACombinationMethod();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	void DataTableInit();

	void AddNeedItem(const int32 itemId, const uint16 needCount);

	UFUNCTION(BlueprintCallable, Category = "Combination Method")
		void AddNeedItem(const int32 itemId, const int32 needCount) { AddNeedItem(itemId, static_cast<uint16>(needCount)); }
public: //Getter Setter
	UFUNCTION(BlueprintSetter)
		void SetCombinationMethodId(const int id);
	UFUNCTION(BlueprintGetter)
		int GetCombinationMethodId() const { return combinationMethodId; }

	TArray<UFuelRequired*>& GetFuels();

private:
	bool IsProduct() const; // 현재 아이템을 생산할 수 있는지
	void ProductItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCombinationMethodId, BlueprintSetter = SetCombinationMethodId)
		int	combinationMethodId;

	UPROPERTY(VisibleAnywhere)
		float productDuration; // 몇초에 1번 생산할지

	/// <summary>
	/// Key : 무슨 아이템이 필요한지에 대한 Id
	/// Value : 몇개가 필요하고 현재 몇개를 소유하고 있는지에 대한 정보
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	TMap<int32, FNeedCount> needItems; // 생산에 필요한 아이템

	/// <summary>
	/// Key : 무슨 아이템이 생상될지에 대한 Id
	/// Value : 현재 몇개가 생산되었는지
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	TMap<int32, FProductCount> productItems; // 생산될 아이템

	UPROPERTY(VisibleAnywhere)
	TArray<UFuelRequired*> fuels; // 연료들

private:
	FTimerHandle productTimerHandle;
};