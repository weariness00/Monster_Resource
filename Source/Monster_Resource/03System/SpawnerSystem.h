// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnerSystem.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTER_RESOURCE_API USpawnerSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnerSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Spawn();

	UFUNCTION()
	void TargetDestroyEvent(AActor* target);

public:
	UPROPERTY(EditDefaultsOnly)
		bool isStart; // 시작하자마자 스폰을 할 것인지

	UPROPERTY(EditDefaultsOnly)
		bool isLoop; // 반복 소환할 것인지
	UPROPERTY(EditDefaultsOnly)
		uint8 loopCount; // Loop를 안한다면 총 몇번을 Loop할 것인지

	UPROPERTY(EditDefaultsOnly)
		bool isRandomTarget; // 타겟을 랜덤하게 스폰할 것인지

	UPROPERTY(EditDefaultsOnly)
		bool isRandomPlace; // 타겟을 랜덤한 위치에 스폰할 것인지

	UPROPERTY(EditDefaultsOnly)
		float spawnDuration; // 몇초 간격으로 스폰할 것인지

	UPROPERTY(EditDefaultsOnly)
		uint8 spawnMaxCount; // 최대 몇마리 스폰이 가능한지

	UPROPERTY(EditDefaultsOnly)
		TArray<AActor*> targets; // 스폰할 타겟들

	UPROPERTY(EditDefaultsOnly)
		TArray<FTransform> spawnPlaces; // 스폰 위치

	uint8 spawnCount; // 현재 몇마리 스폰 되었는지 카운트 ( 없으면 카운트에서 제외 )
	uint8 spawnPlaceIndex; // 스폰 위치 인덱스
	uint8 targetIndex; // 스폰 액터 인덱스

	FTimerHandle spawnTimerHandle;
};