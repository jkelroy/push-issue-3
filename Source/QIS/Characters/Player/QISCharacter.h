// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "QISCharacter.generated.h"


// Forward Declarations
struct FInputActionValue;

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;

class APickup;
class UInventoryComponent;


// Delegate Declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQISCharacter_OnInventoryUpdated, UInventoryComponent*, UpdatedInventory);


UCLASS(config=Game)
class AQISCharacter : public ACharacter
{
	GENERATED_BODY()


public:

	AQISCharacter();

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PickUpItem();

	void SetOverlappingPickup(APickup* Pickup);

	// Delegates
	FQISCharacter_OnInventoryUpdated OnInventoryUpdated;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE APickup* GetOverlappingPickup() const { return OverlappingPickup; }


protected:


private:

	void BindToComponentEvents();

	UFUNCTION()
	void OnInventoryComponentInventoryUpdated(UInventoryComponent* UpdatedInventory);

	/*
	 * Components
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* Inventory;

	UPROPERTY()
	APickup* OverlappingPickup = nullptr;
};
