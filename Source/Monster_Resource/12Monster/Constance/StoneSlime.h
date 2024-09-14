// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterBase.h"
#include "StoneSlime.generated.h"

/**
 * 
 */
UCLASS()
class MONSTER_RESOURCE_API AStoneSlime : public AMonsterBase
{
	GENERATED_BODY()

public:
	AStoneSlime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
