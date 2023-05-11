// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "InventoryTransferRequest.generated.h"


// Forward Declarations
class UInventoryComponent;
class UInventoryItem;


USTRUCT()
struct FInventoryTransferRequest
{
	GENERATED_BODY()


public:

	FInventoryTransferRequest() {}

	FInventoryTransferRequest(UInventoryComponent* InFromInventory, UInventoryComponent* InToInventory, UInventoryItem* InMovingItem, UInventoryItem* InTargetItem = nullptr, int32 InTransferAmount = -1)
		: FromInventory(InFromInventory), ToInventory(InToInventory), MovingItem(InMovingItem), TargetItem(InTargetItem), TransferAmount(InTransferAmount) {};

	bool IsValidRequest() const;

	UPROPERTY()
	UInventoryComponent* FromInventory = nullptr;

	UPROPERTY()
	UInventoryComponent* ToInventory = nullptr;

	UPROPERTY()
	UInventoryItem* MovingItem = nullptr;

	UPROPERTY()
	UInventoryItem* TargetItem = nullptr;

	UPROPERTY()
	int32 TransferAmount = -1;
};