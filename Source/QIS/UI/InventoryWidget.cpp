// Copyright Rob Meade. All Rights Reserved.

#include "InventoryWidget.h"

#include "Components/Button.h"
#include "Components/UniformGridPanel.h"

#include "InventorySlotToolTipWidget.h"
#include "InventorySlotWidget.h"
#include "QIS/Inventory/Components/InventoryComponent.h"
#include "QIS/Inventory/Items/InventoryItem.h"
#include "QIS/Inventory/Items/InventoryItemStaticData.h"


void UInventoryWidget::UpdateInventory(UInventoryComponent* UpdatedInventory)
{
	// TODO: Could be moved to be a property and exposed to BP
	const int32 SlotsPerRow = 9;

	if (UpdatedInventory && InventoryGridPanel)
	{
		// clear the existing items
		InventoryGridPanel->ClearChildren();

		for (int32 InventorySlotIndex = 0; InventorySlotIndex < UpdatedInventory->GetInventoryItemsForDisplay().Num(); InventorySlotIndex++)
		{
			const int32 Row = FMath::FloorToInt(InventorySlotIndex / static_cast<float>(SlotsPerRow));
			const int32 Column = InventorySlotIndex - (SlotsPerRow * Row);

			UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, InventorySlotUserWidget);
			if (InventorySlot)
			{
				UInventoryItem* InventoryItem = UpdatedInventory->GetInventoryItemsForDisplay()[InventorySlotIndex];
				InventorySlot->SetSlotIndex(InventorySlotIndex);
				InventorySlot->SetSlotItem(InventoryItem);

				if (InventoryItem)
				{
					// TODO: This works, but its creating up to 27 tooltip widgets, I could change this so that there's just one, and it sets its data when required
					// in order to do that though, I need access to the data, should I store a pointer in the slot?
					InventorySlotToolTipWidget = CreateWidget<UInventorySlotToolTipWidget>(this, InventorySlotToolTipUserWidget);
					if (InventorySlotToolTipWidget && InventoryItem->GetItemStaticData())
					{
						InventorySlotToolTipWidget->SetToolTip(InventoryItem->GetItemStaticData()->GetItemName(), InventoryItem->GetItemStaticData()->GetItemDescription());
					}
					InventorySlot->SetToolTip(InventorySlotToolTipWidget);
				}

				InventoryGridPanel->AddChildToUniformGrid(InventorySlot, Row, Column);
			}
		}
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BindToEvents();
	CreateInventorySlotToolTipWidget();
}

void UInventoryWidget::BindToEvents()
{
	if (BTN_Close)
	{
		BTN_Close->OnClicked.AddDynamic(this, &UInventoryWidget::OnClickedCloseButton);
	}
}

void UInventoryWidget::CreateInventorySlotToolTipWidget()
{
	// TODO: Use this to create just one instance of the tooltip
	//InventorySlotToolTipWidget = CreateWidget<UInventorySlotToolTipWidget>(this, InventorySlotToolTipUserWidget);
}

void UInventoryWidget::OnClickedCloseButton()
{
	OnCloseButtonClicked.Broadcast();
}
