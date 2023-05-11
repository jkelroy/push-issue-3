// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"

#include "QIS/Inventory/Types/ItemFloatStats.h"

#include "PickupStaticDataEntry.generated.h"


USTRUCT()
struct FPickupStaticDataEntry
{
	GENERATED_BODY()


public:

	FPickupStaticDataEntry() {}

	UPROPERTY(EditAnywhere, Category = "Pickup Static Data Entry")
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, Category = "Pickup Static Data Entry")
	FItemFloatStats StaticPickupFloatStats;
};
