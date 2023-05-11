// Copyright Rob Meade. All Rights Reserved.


#include "InventoryDataSubsystem.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "QIS/DeveloperSettings/InventorySettings.h"
#include "QIS/Inventory/Items/InventoryItemStaticData.h"


bool UInventoryDataSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	// NOTE: Other conditions may need to be checked here rather than just returning true
	return Super::ShouldCreateSubsystem(Outer);
}

void UInventoryDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TArray<FAssetData> FoundAssets;

	const UInventorySettings* InventorySettings = GetDefault<UInventorySettings>();

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByPaths(InventorySettings->InventoryDataDirectories, FoundAssets, true);

	for (const FAssetData& FoundAsset : FoundAssets)
	{
		if (FoundAsset.IsInstanceOf(UInventoryItemStaticData::StaticClass()))
		{
			if (UInventoryItemStaticData* LoadedItemStaticData = Cast<UInventoryItemStaticData>(FoundAsset.GetAsset()))
			{
				InventoryStaticDataAssets.AddUnique(LoadedItemStaticData);

				if (GEngine)
				{
					FString DebugMessage = "Asset Loaded: " + LoadedItemStaticData->GetItemTag().ToString();

					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, DebugMessage);
				}
			}
		}
	}
}

void UInventoryDataSubsystem::Deinitialize()
{
	Super::Deinitialize();

	// TODO: Do I need anything else in here?
}

UInventoryItemStaticData* UInventoryDataSubsystem::FindItemStaticDataByTag(const FGameplayTag ItemTag) const
{
	for (UInventoryItemStaticData* StaticDataAsset : InventoryStaticDataAssets)
	{
		if (StaticDataAsset->GetItemTag().MatchesTag(ItemTag))
		{
			return StaticDataAsset;
		}
	}

	return nullptr;
}
