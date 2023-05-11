// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "QIS/Inventory/Types/ItemFloatStats.h"

#include "InventoryItem.generated.h"


// Forward Declarations
class UInventoryItemStaticData;


UCLASS(Blueprintable)
class QIS_API UInventoryItem : public UObject
{
	GENERATED_BODY()


public:

	void SetStatValue(const FItemFloatStatEntry ItemFloatStatEntry);

	// TODO: Maybe drop all the getters?  The structs are returning copies (might not be ideal in all situations), and if I make the a reference then I may as well just expose the member in the first place
	FORCEINLINE FGameplayTag GetItemTag() const { return ItemTag; }
	FORCEINLINE UInventoryItemStaticData* GetItemStaticData() const { return ItemStaticData; }
	FORCEINLINE FItemFloatStats& GetItemFloatStats() { return ItemFloatStats; }
	FORCEINLINE void SetItemTag(const FGameplayTag InItemTag) { ItemTag = InItemTag; }
	FORCEINLINE void SetItemStaticData(UInventoryItemStaticData* InItemStaticData) { ItemStaticData = InItemStaticData; }

	static bool CompareItemTag(const UInventoryItem* InventoryItem, const FGameplayTag& ItemTag);


protected:


private:

	UPROPERTY(EditAnywhere, Category = "Item")
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, Category = "Item")
	UInventoryItemStaticData* ItemStaticData = nullptr;

	UPROPERTY(EditAnywhere, Category = "Item")
	FItemFloatStats ItemFloatStats;

};
