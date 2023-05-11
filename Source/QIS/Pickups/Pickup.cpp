// Copyright Rob Meade. All Rights Reserved.

#include "Pickup.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "QIS/Characters/Player/QISCharacter.h"
#include "QIS/Inventory/Items/InventoryItem.h"


APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	if (OverlapSphere)
	{
		OverlapSphere->SetupAttachment(RootComponent);
		OverlapSphere->SetSphereRadius(150.f);
		OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (StaticMesh)
	{
		StaticMesh->SetupAttachment(OverlapSphere);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	if (PickupWidget)
	{
		PickupWidget->SetupAttachment(RootComponent);		
	}

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	if (Inventory)
	{
		AddOwnedComponent(Inventory);
	}
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	if(PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}

	if (OverlapSphere)
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
		OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &APickup::OnSphereEndOverlap);
	}

	if (Inventory)
	{
		for (FPickupStaticDataEntry PickupStaticDataEntry : PickupStaticData.StaticData)
		{
			Inventory->AddNewItem(PickupStaticDataEntry.ItemTag, PickupStaticDataEntry.StaticPickupFloatStats.GetFloatStatByTag(FGameplayTag::RequestGameplayTag("Inventory.ItemFloatStat.StackSize")));
		}
	}
}

void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::ShowPickupWidget(const bool bShowWidget) const
{
	if(PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (AQISCharacter* QISCharacter = Cast<AQISCharacter>(OtherActor))
	{
		QISCharacter->SetOverlappingPickup(this);
	}
}

void APickup::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AQISCharacter* QISCharacter = Cast<AQISCharacter>(OtherActor))
	{
		QISCharacter->SetOverlappingPickup(nullptr);
	}
}
