// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../00Game/ActorBase.h"

#include "MonsterBase.generated.h"


UCLASS()
class MONSTER_RESOURCE_API AMonsterBase : public AActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditInstanceOnly)
		int32 id;
};
