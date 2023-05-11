// Copyright Rob Meade. All Rights Reserved.


#include "InventoryTransferRequest.h"

#include "QIS/Inventory/Components/InventoryComponent.h"
#include "QIS/Inventory/Items/InventoryItem.h"


bool FInventoryTransferRequest::IsValidRequest() const
{
    // TODO: Could consider additional checks here also, like whether the moving item has TransferAmount etc
    if (FromInventory && ToInventory && MovingItem && TransferAmount >= -1)
    {
	    return true;
    }

    return false;
}
