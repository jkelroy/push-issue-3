// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"

#include "QIS/Inventory/Types/InventoryTransferRequest.h"

#include "InventoryComponent.generated.h"


// Forward Declarations
class UInventoryItem;


// Delegate Declarations
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryComponent_OnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryComponent_OnInventoryUpdated, UInventoryComponent*, Inventory);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QIS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()


public:	

	UInventoryComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddNewItem(FGameplayTag ItemTag, int32 StackSize);
	void AddItemToInventory(UInventoryItem* ItemToAdd, bool BroadcastOnChange = true);
	void RemoveItemFromInventory(UInventoryItem* ItemToRemove, bool BroadcastOnChange = true);
	bool CanAddItemToInventory(UInventoryItem* QueryItem, bool BroadcastOnChange = true);
	bool AttemptItemTransfer(FInventoryTransferRequest TransferRequestData);

	UInventoryItem* GetInventoryItemWithSmallestStackByTag(FGameplayTag ItemTag) const;
	int32 GetLowestAvailableSlotIndex() const;


	// Testing
	TArray<UInventoryItem*> GetInventoryItemsForDisplay() const;

	// Delegates
	FInventoryComponent_OnInventoryUpdated OnInventoryUpdated;

	FORCEINLINE int32 GetInventorySize() const { return InventorySize; }
	FORCEINLINE TArray<UInventoryItem*> GetInventoryItems() const { return InventoryItems; }


protected:

	
private:

	TArray<UInventoryItem*> GetInventoryItemsByTag(const FGameplayTag& ItemTag) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 InventorySize = 1;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<UInventoryItem*> InventoryItems;
};
