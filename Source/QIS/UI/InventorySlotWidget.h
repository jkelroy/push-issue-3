// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventorySlotWidget.generated.h"


// Forward Declarations
class UImage;
class UTextBlock;

class UInventoryItem;


UCLASS()
class QIS_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	 
	void SetSlotItem(UInventoryItem* InventoryItem);

	FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }
	FORCEINLINE void SetSlotIndex(const int32 Index) { SlotIndex = Index; }


protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;


private:

	int32 SlotIndex;

	/*
	 * UI Widgets
	 */
	UPROPERTY(meta = (BindWidget))
	UImage* SlotBackgroundImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemQuantity = nullptr;
};
