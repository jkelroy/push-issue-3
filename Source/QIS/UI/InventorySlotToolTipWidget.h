// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotToolTipWidget.generated.h"


// Forward Declarations
class UTextBlock;


UCLASS()
class QIS_API UInventorySlotToolTipWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	void SetToolTip(const FString& Name, const FString& Description) const;


protected:


private:

	/*
	 * UI Widgets
	 */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription = nullptr;

};
