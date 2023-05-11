// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "InventoryDataSubsystem.generated.h"


// Forward Declarations
class UInventoryItemStaticData;


UCLASS()
class QIS_API UInventoryDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual UInventoryItemStaticData* FindItemStaticDataByTag(const FGameplayTag ItemTag) const;


protected:

	UPROPERTY()
	TArray<UInventoryItemStaticData*> InventoryStaticDataAssets;


private:


};
