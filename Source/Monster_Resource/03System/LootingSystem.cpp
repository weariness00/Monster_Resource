// Fill out your copyright notice in the Description page of Project Settings.


#include "LootingSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Monster_Resource/00Game/ActorBase.h"
#include "Monster_Resource/00Game/UABGameInstance.h"
#include "Monster_Resource/01Data/LootingTable.h"

// Sets default values for this component's properties
ULootingSystem::ULootingSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULootingSystem::BeginPlay()
{
	Super::BeginPlay();

	AActor* ownerActor = GetOwner();
	if (ownerActor)
	{
		if (AActorBase* actorBase = Cast<AActorBase>(ownerActor))
		{
			GenerateDropItems(actorBase->uniqueId);
		}
	}
}


// Called every frame
void ULootingSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULootingSystem::GenerateDropItems(int id)
{
	UABGameInstance* gi = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gi)
	{
		if (auto lootingData = gi->GetLootingTable(id))
		{
			dropItems = lootingData->Looting();
		}
	}
}