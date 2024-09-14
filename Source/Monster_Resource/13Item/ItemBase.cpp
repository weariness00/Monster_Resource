// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "../00Game/UABGameInstance.h"

AItemBase::AItemBase()
{
	UABGameInstance* ABGameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == ABGameInstance) return;

	data = ABGameInstance->GetItemData(id);
	if (data)
	{
		UE_LOG(LogClass, Log, TEXT("ID : %d\nData Load Success."), id);
	}
	else
	{
		// 데이터 테이블에 없는 레벨일 때
		UE_LOG(LogClass, Warning, TEXT("ID : %d\ndata doesn't exist."), id);
	}
}

AItemBase::~AItemBase()
{
}
