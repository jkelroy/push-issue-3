// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryWidget.generated.h"


// Forward Declarations
class UButton;
class UUniformGridPanel;

class UInventoryComponent;
class UInventorySlotToolTipWidget;
class UInventorySlotWidget;


// Delegate Declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryWidget_OnCloseButtonClicked);


UCLASS()
class QIS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	void UpdateInventory(UInventoryComponent* UpdatedInventory);

	/* Delegates */
	FInventoryWidget_OnCloseButtonClicked OnCloseButtonClicked;


protected:

	virtual void NativeConstruct() override;


private:

	void BindToEvents();
	void CreateInventorySlotToolTipWidget();

	UFUNCTION()
	void OnClickedCloseButton();

	/*
	 * UI Widgets
	 */
	UPROPERTY(EditAnywhere, Category = "User Interfaces")
	TSubclassOf<UUserWidget> InventorySlotUserWidget = nullptr;

	UPROPERTY(EditAnywhere, Category = "User Interfaces")
	TSubclassOf<UUserWidget> InventorySlotToolTipUserWidget = nullptr;

	UPROPERTY()
	UInventorySlotToolTipWidget* InventorySlotToolTipWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Close = nullptr;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* InventoryGridPanel = nullptr;

};
