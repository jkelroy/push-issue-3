// Copyright Rob Meade. All Rights Reserved.

#include "QISPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "QIS/Characters/Player/QISCharacter.h"
#include "QIS/Inventory/Components/InventoryComponent.h"
#include "QIS/Pickups/Pickup.h"
#include "QIS/UI/InventoryWidget.h"


AQISPlayerController::AQISPlayerController()
{
	// ...
}

void AQISPlayerController::BeginPlay()
{
	Super::BeginPlay();

	QISCharacter = Cast<AQISCharacter>(GetPawn());

	AddEnhancedInputMappingContext();
	CreateUIWidgets();
	BindToUIEvents();
	BindToCharacterEvents();
}

void AQISPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) 
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AQISPlayerController::OnJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AQISPlayerController::OnStopJumping);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AQISPlayerController::OnCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AQISPlayerController::OnStopCrouching);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AQISPlayerController::OnMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AQISPlayerController::OnLook);		
		EnhancedInputComponent->BindAction(PickUpItemAction, ETriggerEvent::Started, this, &AQISPlayerController::OnPickUpItem);		
		EnhancedInputComponent->BindAction(DropItemAction, ETriggerEvent::Started, this, &AQISPlayerController::OnDropItem);		
		EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Started, this, &AQISPlayerController::OnUseItem);		
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &AQISPlayerController::OnToggleInventory);
	}
}

void AQISPlayerController::OnMove(const FInputActionValue& Value)
{
	if (QISCharacter)
	{
		QISCharacter->Move(Value);
	}
}

void AQISPlayerController::OnLook(const FInputActionValue& Value)
{
	if (QISCharacter)
	{
		QISCharacter->Look(Value);
	}
}

void AQISPlayerController::OnJump(const FInputActionValue& Value)
{
	if (QISCharacter)
	{
		QISCharacter->Jump();
	}
}

void AQISPlayerController::OnStopJumping(const FInputActionValue& Value)
{
	if (QISCharacter)
	{
		QISCharacter->StopJumping();
	}
}

void AQISPlayerController::OnCrouch(const FInputActionValue& Value)
{
	if (QISCharacter)
	{
		QISCharacter->Crouch();
	}
}

void AQISPlayerController::OnStopCrouching(const FInputActionValue& Value)
{
	if (QISCharacter)
	{
		QISCharacter->UnCrouch();
	}
}

void AQISPlayerController::OnPickUpItem(const FInputActionValue& Value)
{
	if (QISCharacter)
	{
		QISCharacter->PickUpItem();
	}
}

void AQISPlayerController::OnDropItem(const FInputActionValue& Value)
{
	// TODO:
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, TEXT("Drop Item"));
	}
}

void AQISPlayerController::OnUseItem(const FInputActionValue& Value)
{
	// TODO:
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, TEXT("Use Item"));
	}
}

void AQISPlayerController::OnToggleInventory(const FInputActionValue& Value)
{
	ToggleInventory();
}

void AQISPlayerController::AddEnhancedInputMappingContext() const
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AQISPlayerController::CreateUIWidgets()
{
	if (InventoryUserWidget)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(this, InventoryUserWidget);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			ToggleWidgetVisibility(InventoryWidget);
		}
	}
}

void AQISPlayerController::BindToUIEvents()
{
	if (InventoryWidget)
	{
		InventoryWidget->OnCloseButtonClicked.AddDynamic(this, &AQISPlayerController::OnInventoryCloseButtonClicked);
	}
}

void AQISPlayerController::BindToCharacterEvents()
{
	if (QISCharacter)
	{
		QISCharacter->OnInventoryUpdated.AddDynamic(this, &AQISPlayerController::OnQISCharacterInventoryUpdated);
	}
}

void AQISPlayerController::OnQISCharacterInventoryUpdated(UInventoryComponent* UpdatedInventory)
{
	if (InventoryWidget)
	{
		InventoryWidget->UpdateInventory(UpdatedInventory);
	}
}

void AQISPlayerController::OnInventoryCloseButtonClicked()
{
	ToggleInventory();
}

void AQISPlayerController::ToggleInventory()
{
	ToggleWidgetVisibility(InventoryWidget);

	if (InventoryWidget)
	{
		if (InventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			SetInputModeForGame();
		}
		else
		{
			FlushPressedKeys();
			SetInputModeForUI(InventoryWidget);
		}
	}
}

void AQISPlayerController::SetInputModeForUI(const UUserWidget* WidgetToFocus)
{
	if (WidgetToFocus)
	{
		FInputModeUIOnly InputModeUIOnly;
		InputModeUIOnly.SetWidgetToFocus(WidgetToFocus->GetCachedWidget());		
		SetInputMode(InputModeUIOnly);

		bShowMouseCursor = true;		
	}
}

void AQISPlayerController::SetInputModeForGame()
{
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);

	bShowMouseCursor = false;
}

void AQISPlayerController::ToggleWidgetVisibility(UUserWidget* Widget)
{
	if (Widget)
	{
		switch (Widget->GetVisibility())
		{
			case ESlateVisibility::Visible:
				Widget->SetVisibility(ESlateVisibility::Hidden);
				break;
			case ESlateVisibility::Collapsed:
				Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				break;
			case ESlateVisibility::Hidden:
				Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				break;
			case ESlateVisibility::HitTestInvisible:
				Widget->SetVisibility(ESlateVisibility::Hidden);
				break;
			case ESlateVisibility::SelfHitTestInvisible:
				Widget->SetVisibility(ESlateVisibility::Hidden);
				break;
			default:
				break;
		}
	}
}
