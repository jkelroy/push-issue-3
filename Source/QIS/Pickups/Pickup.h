// Copyright Rob Meade. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"

#include "QIS/Inventory/Components/InventoryComponent.h"
#include "QIS/Inventory/Types/PickupStaticData.h"

#include "Pickup.generated.h"


// Forward Declarations
class USphereComponent;
class UStaticMeshComponent;
class UWidgetComponent;

class AQISCharacter;


UCLASS()
class QIS_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	

	APickup();

	virtual void Tick(float DeltaTime) override;
	void ShowPickupWidget(bool bShowWidget) const;

	FORCEINLINE UInventoryComponent* GetInventory() const { return Inventory; }


protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



private:	

	UPROPERTY(EditAnywhere, Category = "Pickup|Components")
	USphereComponent* OverlapSphere = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Pickup|Components")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Pickup|Components")
	UWidgetComponent* PickupWidget;	

	UPROPERTY(VisibleAnywhere, Category = "Pickup|Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	FPickupStaticData PickupStaticData;
};
