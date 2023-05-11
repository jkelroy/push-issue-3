// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"

#include "ItemFloatStatEntry.generated.h"


USTRUCT()
struct FItemFloatStatEntry
{
	GENERATED_BODY()


public:

	FItemFloatStatEntry() {};
	FItemFloatStatEntry(const FGameplayTag InTag, const float InStatValue) : StatTag(InTag), StatValue(InStatValue) {}

	UPROPERTY(EditAnywhere, Category = "Item Float Stat Entry")
	FGameplayTag StatTag;

	UPROPERTY(EditAnywhere, Category = "Item Float Stat Entry")
	float StatValue = 0.f;
};