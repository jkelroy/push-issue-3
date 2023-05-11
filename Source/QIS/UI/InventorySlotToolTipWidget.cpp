// Copyright Rob Meade. All Rights Reserved.


#include "InventorySlotToolTipWidget.h"

#include "Components/TextBlock.h"


void UInventorySlotToolTipWidget::SetToolTip(const FString& Name, const FString& Description) const
{
	if (ItemName)
	{
		ItemName->SetText(FText::FromString(Name));
	}

	if (ItemDescription)
	{
		ItemDescription->SetText(FText::FromString(Description));
	}
}
