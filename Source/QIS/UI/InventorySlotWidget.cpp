// Copyright Rob Meade. All Rights Reserved.

#include "InventorySlotWidget.h"

#include "InputCoreTypes.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Input/Events.h"
#include "Input/Reply.h"
#include "Layout/Geometry.h"

#include "InventorySlotToolTipWidget.h"
#include "QIS/Inventory/Items/InventoryItem.h"
#include "QIS/Inventory/Items/InventoryItemStaticData.h"


void UInventorySlotWidget::SetSlotItem(UInventoryItem* InventoryItem)
{
	if (InventoryItem)
	{
		ItemImage->SetBrushFromSoftTexture(InventoryItem->GetItemStaticData()->GetItemInventoryTexture());
		ItemImage->ColorAndOpacity = FLinearColor(1.f, 1.f, 0.f, 1.f);

		ItemQuantity->SetText(FText::AsNumber(InventoryItem->GetItemFloatStats().GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize"))));
	}
	else
	{
		ItemImage->SetBrushFromTexture(nullptr);
		ItemImage->ColorAndOpacity = FLinearColor::Transparent;

		ItemQuantity->SetText(FText::FromString(""));
	}
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// left-click behaviour
		UE_LOG(LogTemp, Warning, TEXT("Slot Index: %d clicked (left mouse button)"), SlotIndex);
	}
	else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		// right-click behaviour
		UE_LOG(LogTemp, Warning, TEXT("Slot Index: %d clicked (right mouse button)"), SlotIndex);
	}

	return FReply::Handled();
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// highlight hover slot
	if (SlotBackgroundImage)
	{
		SlotBackgroundImage->SetBrushTintColor(FSlateColor(FLinearColor(1.f, 1.f, 0.f, 1.f)));
		SlotBackgroundImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	// highlight hover slot
	if (SlotBackgroundImage)
	{
		SlotBackgroundImage->SetBrushTintColor(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)));
		SlotBackgroundImage->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f, 1.f));
	}
}
