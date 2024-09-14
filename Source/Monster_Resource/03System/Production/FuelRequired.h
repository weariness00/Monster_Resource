// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FuelEnum.h"
#include "Components/ActorComponent.h"
#include "FuelRequired.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTER_RESOURCE_API UFuelRequired : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFuelRequired();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ConnectFuel();
	void DisConnectFuel();

public: //Getter Setter
	bool IsConnect() const { return isConnect; }
	float GetFuelAmount() const { return needFuelAmount; }

	FuelEnum GetFuelType() const { return fuelType; }

protected:
	UPROPERTY(EditAnywhere)
	FuelEnum fuelType;
	UPROPERTY(EditAnywhere)
	float needFuelAmount; // 필요 연료량
	UPROPERTY(VisibleAnywhere)
	bool isConnect;
};