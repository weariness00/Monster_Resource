// Fill out your copyright notice in the Description page of Project Settings.

#include "CombinationMethod.h"
#include "../../00Game/UABGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Monster_Resource/03System/Production/FuelRequired.h"
#include "Monster_Resource/01Data/ProductionTable.h"

UABGameInstance* ACombinationMethod::gameInstance = nullptr;
FTimerManager* ACombinationMethod::timerManager = nullptr;

void ACombinationMethod::StaticClear()
{
	gameInstance = nullptr;
	timerManager = nullptr;
}

// Sets default values for this component's properties
ACombinationMethod::ACombinationMethod()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ACombinationMethod::BeginPlay()
{
	Super::BeginPlay();

	if (gameInstance == nullptr)
	{
		gameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	}

	if(timerManager == nullptr)
	{
		timerManager = &GetWorld()->GetTimerManager();
	}
	
	GetComponents(fuels);
}


// Called every frame
void ACombinationMethod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	// ...
}

void ACombinationMethod::DataTableInit()
{
	auto* table = gameInstance->GetProductionTable(combinationMethodId);
	if(table == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ID : [%d] Do Not Find Method."), combinationMethodId);
		return;
	}

	productDuration = table->productDuration;
	for (const auto& [itemId, needCount] : table->needItems)
	{
		needItems.Emplace(itemId, { needCount, 0 });
	}

	for (const auto& [itemId, productCount] : table->productItems)
	{
		productItems.Emplace(itemId, { productCount, 0 });
	}
}

void ACombinationMethod::AddNeedItem(const int32 itemId, const uint16 needCount)
{
	if(needItems.Contains(itemId))
	{
		needItems[itemId].currentItem += needCount;

		// 아이템을 추가한뒤 생산할 준비가 되었는지 판단
		if(IsProduct() && !timerManager->IsTimerActive(productTimerHandle))
		{
			timerManager->SetTimer(productTimerHandle, this, &ACombinationMethod::ProductItem, productDuration, false);
		}
	}
}

void ACombinationMethod::SetCombinationMethodId(const int id)
{
	combinationMethodId = id;
	DataTableInit();
}

TArray<UFuelRequired*>& ACombinationMethod::GetFuels()
{
	return fuels; 
}

bool ACombinationMethod::IsProduct() const
{
	for (const auto& [itemId, need] : needItems)
	{
		if(need.needItem > need.currentItem)
		{
			return false;
		}
	}

	return true;
}

void ACombinationMethod::ProductItem()
{
	// 생산에 사용된 아이템 제거
	for (auto& [itemId, need] : needItems)
	{
		need.currentItem -= need.needItem;
	}

	// 아이템 생산
	for(auto& [itemId, product] : productItems)
	{
		product.currentItem += product.productItem;
	}

	if (IsProduct())
	{
		timerManager->SetTimer(productTimerHandle, this, &ACombinationMethod::ProductItem, productDuration, false);
	}
}