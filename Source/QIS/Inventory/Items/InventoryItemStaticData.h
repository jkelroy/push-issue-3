// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "QIS/Inventory/Types/InventoryCategory.h"
#include "QIS/INventory/Types/ItemFloatStats.h"

#include "InventoryItemStaticData.generated.h"


// Forward Declarations
class UTexture2D;

class UInventoryItem;
class UInventoryComponent;


UCLASS()
class QIS_API UInventoryItemStaticData : public UDataAsset
{
	GENERATED_BODY()


public:

	UInventoryItem* CreateItemInstance(UInventoryComponent* ForComponent);

	FORCEINLINE FGameplayTag GetItemTag() const { return ItemTag; }
	FORCEINLINE FString GetItemName() const { return Name; }
	FORCEINLINE FString GetItemDescription() const { return Description; }
	FORCEINLINE TSoftObjectPtr<UTexture2D> GetItemInventoryTexture() { return InventoryTexture; }

	FORCEINLINE FItemFloatStats GetStaticItemFloatStats() const { return StaticItemFloatStats; }


protected:


private:

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data|Item")
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data|Item")
	TSubclassOf<UInventoryItem> ItemCreationClass;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data")
	FString Name;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data")
	FString Description;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data")
	FItemFloatStats DefaultItemFloatStats;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data")
	FItemFloatStats StaticItemFloatStats;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data|Pickup")
	TSoftObjectPtr<UStaticMesh> PickupStaticMesh;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data|Inventory")
	TSoftObjectPtr<UTexture2D> InventoryTexture = nullptr;

	UPROPERTY(EditAnywhere, Category = "Inventory Item Static Data|Inventory")
	EInventoryCategory InventoryCategory = EInventoryCategory::None;
};
