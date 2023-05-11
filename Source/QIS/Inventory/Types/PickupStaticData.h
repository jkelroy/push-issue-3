// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "QIS/Inventory/Types/PickupStaticDataEntry.h"

#include "PickupStaticData.generated.h"


USTRUCT()
struct FPickupStaticData
{
	GENERATED_BODY()


public:

	FPickupStaticData() {}

	UPROPERTY(EditAnywhere, Category = "Pickup Static Data")
	TArray<FPickupStaticDataEntry> StaticData;
};
