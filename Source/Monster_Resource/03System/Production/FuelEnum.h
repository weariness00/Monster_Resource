// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class FuelEnum : uint8
{
	ELECTRIC UMETA(DisplayName = "Electric"),
	MANA UMETA(DisplayName = "Mana"),
};