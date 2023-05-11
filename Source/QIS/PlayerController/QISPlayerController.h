// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "QISPlayerController.generated.h"


// Forward Declarations
class UInputAction;
class UInputMappingContext;
class UUserWidget;

class AQISCharacter;
class UInventoryComponent;
class UInventoryWidget;


UCLASS()
class QIS_API AQISPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	AQISPlayerController();


protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	/*
	 * Player Input
	 */
	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	void OnStopJumping(const FInputActionValue& Value);
	void OnCrouch(const FInputActionValue& Value);
	void OnStopCrouching(const FInputActionValue& Value);
	void OnPickUpItem(const FInputActionValue& Value);
	void OnDropItem(const FInputActionValue& Value);
	void OnUseItem(const FInputActionValue& Value);
	void OnToggleInventory(const FInputActionValue& Value);


private:

	void AddEnhancedInputMappingContext() const;
	void CreateUIWidgets();
	void BindToUIEvents();
	void BindToCharacterEvents();

	UFUNCTION()
	void OnQISCharacterInventoryUpdated(UInventoryComponent* UpdatedInventory);

	/*
	 * UI - Inventory
	 */
	UFUNCTION()
	void OnInventoryCloseButtonClicked();

	void ToggleInventory();

	/*
	 * UI - Helpers
	 */
	void SetInputModeForUI(const UUserWidget* WidgetToFocus);
	void SetInputModeForGame();
	void ToggleWidgetVisibility(UUserWidget* Widget);

	/*
	 * Input Actions/Mappings
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickUpItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DropItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UseItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleInventoryAction;

	/*
	 * UI Widgets
	 */
	UPROPERTY(EditAnywhere, Category = "User Interfaces")
	TSubclassOf<UUserWidget> InventoryUserWidget = nullptr;

	UPROPERTY()
	UInventoryWidget* InventoryWidget = nullptr;


	UPROPERTY()
	AQISCharacter* QISCharacter = nullptr;
};
