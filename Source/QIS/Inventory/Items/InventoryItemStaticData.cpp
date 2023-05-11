// Copyright Rob Meade. All Rights Reserved.


#include "InventoryItemStaticData.h"

#include "InventoryItem.h"
#include "QIS/Inventory/Components/InventoryComponent.h"


UInventoryItem* UInventoryItemStaticData::CreateItemInstance(UInventoryComponent* ForComponent)
{
	if (!IsValid(ForComponent))
	{
		return nullptr;
	}

	UInventoryItem* NewItem = NewObject<UInventoryItem>(ForComponent, ItemCreationClass);
	if (IsValid(NewItem))
	{
		NewItem->SetItemTag(ItemTag);
		NewItem->SetItemStaticData(this);

		for (const FItemFloatStatEntry ItemFloatStatEntry : DefaultItemFloatStats.FloatStats)
		{
			NewItem->SetStatValue(ItemFloatStatEntry);
		}
	}

	return NewItem;
}
