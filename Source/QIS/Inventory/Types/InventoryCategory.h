// Copyright Rob Meade. All Rights Reserved.

#pragma once

UENUM()
enum class EInventoryCategory : uint8
{

	None	UMETA(DisplayName = "None"),
	Main	UMETA(DisplayName = "Main"),

	NUM		UMETA(Hidden)
};