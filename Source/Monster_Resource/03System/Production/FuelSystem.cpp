// Fill out your copyright notice in the Description page of Project Settings.


#include "FuelSystem.h"
#include "CombinationMethod.h"
#include "FuelRequired.h"

// Sets default values
AFuelSystem::AFuelSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFuelSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuelSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuelSystem::AddProduct(ACombinationMethod* product)
{
	for (UFuelRequired* fuel : product->GetFuels())
	{
		if (fuelType == fuel->GetFuelType())
		{
			float remainingFuel = productFuel - useFuel;
			if (remainingFuel > 0 && fuel->GetFuelAmount() < remainingFuel)
			{
				fuel->ConnectFuel();
			}
			else
			{
				if (auto find = needFuelProducts.FindByPredicate([product](const TPair<int, TQueue<UFuelRequired*>>& Pair) {return Pair.Key == product->GetCombinationMethodId(); }))
				{
					find->Value.Enqueue(fuel);
				}
			}
			return;
		}
	}
}
