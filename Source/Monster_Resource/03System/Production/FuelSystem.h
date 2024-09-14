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
	// 정렬 함수 정의
	struct FComparePairs {
		bool operator()(const TPair<int, TQueue<UFuelRequired*>>& A, const TPair<int, TQueue<UFuelRequired*>>& B) const {
			return A.Key < B.Key;  // Key 값에 따른 오름차순 정렬
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
	float needMaxFuel; // 필요한 최대 연료량
	UPROPERTY(VisibleAnywhere)
	float useFuel; // 사용되고 있는 연료량
	UPROPERTY(VisibleAnywhere)
	float productFuel; // 생산되고 있는 연료량

	// Key : Product Id
	// Value : Product 클래스
	TArray<TPair<int, TQueue<UFuelRequired*>>> needFuelProducts; // 연료가 필요한 건물
	TArray<TPair<int, TQueue<UFuelRequired*>>> hasFuelProducts; // 연료를 가지고 있는 건물
};
