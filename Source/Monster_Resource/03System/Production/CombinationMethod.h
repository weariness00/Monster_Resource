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
	uint16 needItem; // �ʿ��� ������ ����
	UPROPERTY(EditAnywhere)
	uint16 currentItem; // ���� ������ ������ ����
};

USTRUCT()
struct FProductCount
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	uint16 productItem; // ����� ������ ����
	UPROPERTY(EditAnywhere)
	uint16 currentItem; // ����� ������ ����
};

// ���չ�
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
	bool IsProduct() const; // ���� �������� ������ �� �ִ���
	void ProductItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCombinationMethodId, BlueprintSetter = SetCombinationMethodId)
		int	combinationMethodId;

	UPROPERTY(VisibleAnywhere)
		float productDuration; // ���ʿ� 1�� ��������

	/// <summary>
	/// Key : ���� �������� �ʿ������� ���� Id
	/// Value : ��� �ʿ��ϰ� ���� ��� �����ϰ� �ִ����� ���� ����
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	TMap<int32, FNeedCount> needItems; // ���꿡 �ʿ��� ������

	/// <summary>
	/// Key : ���� �������� ��������� ���� Id
	/// Value : ���� ��� ����Ǿ�����
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	TMap<int32, FProductCount> productItems; // ����� ������

	UPROPERTY(VisibleAnywhere)
	TArray<UFuelRequired*> fuels; // �����

private:
	FTimerHandle productTimerHandle;
};