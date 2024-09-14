// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FuelEnum.h"
#include "GameFramework/Actor.h"
#include "FuelSystem.generated.h"

class UFuelRequired;
class ACombinationMethod;

UCLASS()
class MONSTER_RESOURCE_API AFuelSystem : public AActor
{
	GENERATED_BODY()

private:
	// ���� �Լ� ����
	struct FComparePairs {
		bool operator()(const TPair<int, TQueue<UFuelRequired*>>& A, const TPair<int, TQueue<UFuelRequired*>>& B) const {
			return A.Key < B.Key;  // Key ���� ���� �������� ����
		}
	};
	
public:	
	// Sets default values for this actor's properties
	AFuelSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddProduct(ACombinationMethod* product);

public:
	UPROPERTY(VisibleAnywhere)
	FuelEnum fuelType;

	UPROPERTY(VisibleAnywhere)
	float needMaxFuel; // �ʿ��� �ִ� ���ᷮ
	UPROPERTY(VisibleAnywhere)
	float useFuel; // ���ǰ� �ִ� ���ᷮ
	UPROPERTY(VisibleAnywhere)
	float productFuel; // ����ǰ� �ִ� ���ᷮ

	// Key : Product Id
	// Value : Product Ŭ����
	TArray<TPair<int, TQueue<UFuelRequired*>>> needFuelProducts; // ���ᰡ �ʿ��� �ǹ�
	TArray<TPair<int, TQueue<UFuelRequired*>>> hasFuelProducts; // ���Ḧ ������ �ִ� �ǹ�
};
