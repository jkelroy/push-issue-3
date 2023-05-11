// Copyright Rob Meade. All Rights Reserved.

#include "ItemFloatStats.h"


FItemFloatStatEntry* FItemFloatStats::GetFloatStatEntryPtr(const FGameplayTag& StatTag)
{
	for (FItemFloatStatEntry& ItemFloatStatEntry : FloatStats)
	{
		if (ItemFloatStatEntry.StatTag == StatTag)
		{
			return &ItemFloatStatEntry;
		}
	}

	return nullptr;
}

void FItemFloatStats::SetItemStat(const FItemFloatStatEntry InItemFloatStatEntry)
{
	// TODO: Maybe temp
	if (FItemFloatStatEntry* ItemFloatStatEntry = GetFloatStatEntryPtr(InItemFloatStatEntry.StatTag))
	{
		ItemFloatStatEntry->StatValue = InItemFloatStatEntry.StatValue;
	}
	else
	{
		FloatStats.Add(InItemFloatStatEntry);		
	}
}

float FItemFloatStats::GetFloatStatByTag(const FGameplayTag& StatTag) const
{
	for (FItemFloatStatEntry ItemFloatStatEntry : FloatStats)
	{
		if (ItemFloatStatEntry.StatTag == StatTag)
		{
			return ItemFloatStatEntry.StatValue;
		}
	}

	return -1.f;
}
