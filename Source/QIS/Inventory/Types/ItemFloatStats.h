// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "ItemFloatStatEntry.h"

#include "ItemFloatStats.generated.h"


USTRUCT()
struct FItemFloatStats
{
	GENERATED_BODY()


public:

	FItemFloatStatEntry* GetFloatStatEntryPtr(const FGameplayTag& StatTag);
	void SetItemStat(const FItemFloatStatEntry InItemFloatStatEntry);
	float GetFloatStatByTag(const FGameplayTag& StatTag) const;

	UPROPERTY(EditAnywhere)
	TArray<FItemFloatStatEntry> FloatStats;
};