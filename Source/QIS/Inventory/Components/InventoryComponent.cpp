// Copyright Rob Meade. All Rights Reserved.

#include "InventoryComponent.h"

#include "QIS/Inventory/Items/InventoryItemStaticData.h"
#include "QIS/Inventory/Items/InventoryItem.h"
#include "QIS/Inventory/Subsystem/InventoryDataSubsystem.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddNewItem(const FGameplayTag ItemTag, int32 StackSize)
{
	UInventoryItemStaticData* ItemStaticData = nullptr;

	if (const UInventoryDataSubsystem* InventoryDataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UInventoryDataSubsystem>())
	{
		ItemStaticData = InventoryDataSubsystem->FindItemStaticDataByTag(ItemTag);
	}

	if (!ItemStaticData)
	{
		return;
	}

	if (UInventoryItem* NewItem = ItemStaticData->CreateItemInstance(this))
	{
		// TODO: Could add a check here to get the MaxStackSize and clamp the StackSize between 0 and MaxStackSize perhaps
		NewItem->SetStatValue(FItemFloatStatEntry(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize"), StackSize));
		InventoryItems.AddUnique(NewItem);
	}
}

void UInventoryComponent::AddItemToInventory(UInventoryItem* ItemToAdd, bool BroadcastOnChange)
{
	if (IsValid(ItemToAdd) && !InventoryItems.Contains(ItemToAdd))
	{
		InventoryItems.Add(ItemToAdd);
		if (BroadcastOnChange)
		{
			OnInventoryUpdated.Broadcast(this);
		}
	}
}

void UInventoryComponent::RemoveItemFromInventory(UInventoryItem* ItemToRemove, bool BroadcastOnChange)
{
	InventoryItems.Remove(ItemToRemove);
	if (BroadcastOnChange)
	{
		OnInventoryUpdated.Broadcast(this);
	}
}

// TODO: Not sure if this needs to broadcastonchange unless this function will actually change the inventory, e.g. add the item if its possible to
bool UInventoryComponent::CanAddItemToInventory(UInventoryItem* QueryItem, bool BroadcastOnChange)
{
	// TODO: Add logic to check conditions here (inventory size/space remaining etc)

	// TODO: Initially only looks at free slots in the inventory, not stack sizes
	// the following code could be simplified but leaving as is ready for the more complex logic here
	if (InventoryItems.Num() < InventorySize)
	{
		return true;
	}
	else
	{
		return false;		
	}
}

bool UInventoryComponent::AttemptItemTransfer(FInventoryTransferRequest TransferRequestData)
{
	// TODO: Need to consider what is sending the broadcast notifications - this function, or the functions that this function calls
	if (TransferRequestData.IsValidRequest())
	{
		if (TransferRequestData.TargetItem)
		{
			const float TargetItemMaxStackSize = TransferRequestData.TargetItem->GetItemStaticData()->GetStaticItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.MaxStackSize"));
			const float TargetItemCurrentStackSize = TransferRequestData.TargetItem->GetItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize"));
			const float MovingItemCurrentStackSize = TransferRequestData.MovingItem->GetItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize"));

			if (TargetItemCurrentStackSize + TransferRequestData.TransferAmount <= TargetItemMaxStackSize)
			{
				TransferRequestData.TargetItem->GetItemFloatStats().SetItemStat(FItemFloatStatEntry(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize"), TargetItemCurrentStackSize + TransferRequestData.TransferAmount));
				TransferRequestData.FromInventory->RemoveItemFromInventory(TransferRequestData.MovingItem);

				// TODO: Not sure about this being here, it might be better to have some kind of "JustAddQuantityToExistingItem" function, and then call it in there
				OnInventoryUpdated.Broadcast(this);

				return true;
			}
			else
			{
				const float QuantityToFillExistingItemStack = TargetItemMaxStackSize - TargetItemCurrentStackSize;

				// top up existing item
				TransferRequestData.TargetItem->GetItemFloatStats().SetItemStat(FItemFloatStatEntry(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize"), TargetItemCurrentStackSize + QuantityToFillExistingItemStack));

				// reduce stats on moving item
				TransferRequestData.MovingItem->GetItemFloatStats().SetItemStat(FItemFloatStatEntry(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize"), MovingItemCurrentStackSize - QuantityToFillExistingItemStack));

				// if remainder AND can add item
				if (TransferRequestData.TransferAmount - QuantityToFillExistingItemStack > 0)
				{
					if (CanAddItemToInventory(TransferRequestData.MovingItem))
					{
						// set slot
						TransferRequestData.MovingItem->GetItemFloatStats().SetItemStat(FItemFloatStatEntry(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.SlotIndex"), GetLowestAvailableSlotIndex()));

						TransferRequestData.FromInventory->RemoveItemFromInventory(TransferRequestData.MovingItem);
						TransferRequestData.ToInventory->AddItemToInventory(TransferRequestData.MovingItem);

						return true;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Inventory is full"));
						return false;
					}
				}
				else
				{
					return true;
				}
			}
		}
		else
		{
			if (CanAddItemToInventory(TransferRequestData.MovingItem))
			{
				// set slot
				TransferRequestData.MovingItem->GetItemFloatStats().SetItemStat(FItemFloatStatEntry(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.SlotIndex"), GetLowestAvailableSlotIndex()));

				TransferRequestData.FromInventory->RemoveItemFromInventory(TransferRequestData.MovingItem);
				TransferRequestData.ToInventory->AddItemToInventory(TransferRequestData.MovingItem);

				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

UInventoryItem* UInventoryComponent::GetInventoryItemWithSmallestStackByTag(FGameplayTag ItemTag) const
{
	UInventoryItem* InventoryItemWithSmallestStack = nullptr;

	for (UInventoryItem* InventoryItem : GetInventoryItemsByTag(ItemTag))
	{
		if (!InventoryItemWithSmallestStack)
		{
			InventoryItemWithSmallestStack = InventoryItem;
		}
		else
		{
			// TODO: Common/mandatory float stats could perhaps have helper functions
			if (InventoryItem->GetItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize")) < InventoryItemWithSmallestStack->GetItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize")))
			{
				InventoryItemWithSmallestStack = InventoryItem;
			}
		}
	}

	return InventoryItemWithSmallestStack;
}

int32 UInventoryComponent::GetLowestAvailableSlotIndex() const
{
	// -1 indicates no available slots
	int32 LowestSlotIndex = -1;

	// inventory items hold their established slot indexes
	// i need to find the lowest slot index that hasn't been used

	if (InventoryItems.Num() == InventorySize)
	{
		return LowestSlotIndex;
	}

	for (int32 SlotIndex = 0; SlotIndex < InventorySize; SlotIndex++)
	{
		LowestSlotIndex = SlotIndex;

		for (UInventoryItem* InventoryItem : InventoryItems)
		{
			int32 InventoryItemSlotIndex = InventoryItem->GetItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.SlotIndex"));

			if (SlotIndex == InventoryItemSlotIndex)
			{
				LowestSlotIndex = -1;
				break;
			}
		}

		if (LowestSlotIndex > -1)
		{
			break;
		}
	}

	return LowestSlotIndex;
}

TArray<UInventoryItem*> UInventoryComponent::GetInventoryItemsForDisplay() const
{
	TArray<UInventoryItem*> InventoryItemsForDisplay;
	InventoryItemsForDisplay.Init(nullptr, InventorySize);

	for (UInventoryItem* InventoryItem : InventoryItems)
	{
		if (InventoryItem)
		{
			const int32 SlotIndex = InventoryItem->GetItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.SlotIndex"));
			InventoryItemsForDisplay[SlotIndex] = InventoryItem;
		}
	}

	return InventoryItemsForDisplay;
}

TArray<UInventoryItem*> UInventoryComponent::GetInventoryItemsByTag(const FGameplayTag& ItemTag) const
{
	return InventoryItems.FilterByPredicate([&ItemTag](const UInventoryItem* InventoryItem)
		{
			return UInventoryItem::CompareItemTag(InventoryItem, ItemTag);
		}
	);
}
