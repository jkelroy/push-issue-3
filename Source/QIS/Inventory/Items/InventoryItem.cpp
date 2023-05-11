// Copyright Rob Meade. All Rights Reserved.

#include "InventoryItem.h"


void UInventoryItem::SetStatValue(const FItemFloatStatEntry ItemFloatStatEntry)
{
	ItemFloatStats.SetItemStat(ItemFloatStatEntry);
}

bool UInventoryItem::CompareItemTag(const UInventoryItem* InventoryItem, const FGameplayTag& ItemTag)
{
	return InventoryItem->GetItemTag() == ItemTag;
}
