// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerSystem.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USpawnerSystem::USpawnerSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	spawnPlaceIndex = 0;
	targetIndex = 0;

	// ...
}


// Called when the game starts
void USpawnerSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if (isLoop)
	{
		GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, [this]() { this->Spawn(); }, spawnDuration, true);
	}
	else
	{
		if (isStart) --loopCount;
		GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, [this]() { this->Spawn(); }, spawnDuration, true, loopCount);
	}
	if (isStart)
	{
		Spawn();
	}
}


// Called every frame
void USpawnerSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpawnerSystem::Spawn()
{
	if (++spawnCount < spawnMaxCount)
	{
		UWorld* World = GetWorld();
		if (World == nullptr) return;
		if (!targets.IsValidIndex(targetIndex) || !spawnPlaces.IsValidIndex(spawnPlaceIndex)) return;

		// 액터를 지정된 위치와 회전에 따라 소환합니다
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner(); // 소환된 액터의 소유자 설정
		SpawnParams.Instigator = GetOwner()->GetInstigator();

		TSubclassOf<AActor> target = targets[targetIndex]->GetClass();
		FTransform place = spawnPlaces[spawnPlaceIndex];

		// 액터 소환
		AActor* SpawnedActor = World->SpawnActor<AActor>(target, place, SpawnParams);
		
		targetIndex = isRandomTarget ? FMath::RandRange(0, targets.Num()) : (targetIndex + 1) % targets.Num();
		spawnPlaceIndex = isRandomPlace ? FMath::RandRange(0, spawnPlaces.Num()) : (spawnPlaceIndex + 1) % spawnPlaces.Num();

		if (SpawnedActor)
		{
			SpawnedActor->OnDestroyed.AddDynamic(this, &USpawnerSystem::TargetDestroyEvent);
			UE_LOG(LogTemp, Log, TEXT("Spawn Actor: %s"), *SpawnedActor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is Failed Spawn Actor."), *this->GetName());
		}
	}

}

void USpawnerSystem::TargetDestroyEvent(AActor* target)
{
	--this->spawnCount;
}