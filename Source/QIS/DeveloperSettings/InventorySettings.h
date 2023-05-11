// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "InventorySettings.generated.h"


UCLASS(Config=Game, DefaultConfig)
class QIS_API UInventorySettings : public UDeveloperSettings
{
	GENERATED_BODY()


public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Directories")
	TArray<FName> InventoryDataDirectories;


protected:


private:

	
};
