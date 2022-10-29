// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "ShooterCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AItem::AItem() :
	ItemName(FString("ItemName")), ItemCount(0), ItemRarity(EItemRarity::EIR_Common), ItemState(EItemState ::EIS_Pickup),
	ItemInterpStartLocation(FVector(0.f)), CameraTargetLocation(FVector(0.f)), ZCurveTime(0.7f),
	InterpInitialYawOffset(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

	CollisionBox->SetupAttachment(ItemMesh);

	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Pickup Widget"));
	PickupWidget->SetupAttachment(GetRootComponent());

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	

	if(PickupWidget)
	PickupWidget->SetVisibility(false);

	SetActiveStars();

	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereBeginOverlap);

	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);

	SetItemProperties(ItemState);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ItemInterp(DeltaTime);
}



void AItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AShooterCharacter* Character = Cast<AShooterCharacter>(OtherActor);

		if (Character)
		{
			Character->UpdateOverlappedItemCount(1);
		}
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	if (OtherActor)
	{
		AShooterCharacter* Character = Cast<AShooterCharacter>(OtherActor);

		if (Character)
		{
			Character->UpdateOverlappedItemCount(-1);
		}
	}
}

void AItem::SetActiveStars()
{
	for (int32 i = 0;i <= 5;i++)
	{
		ActiveStars.Add(false);
	}

	switch (ItemRarity)
	{
	case EItemRarity::EIR_Damaged:
		ActiveStars[1] = true;
		break;
	case EItemRarity::EIR_Common:
		ActiveStars[1] = ActiveStars[2] = true;
		break;
	case EItemRarity::EIR_Uncommon:
		ActiveStars[1] = ActiveStars[2] = ActiveStars[3] = true;
		break;
	case EItemRarity::EIR_Rare:
		ActiveStars[1] = ActiveStars[2] = ActiveStars[3] = ActiveStars[4] = true;
		break;
	case EItemRarity::EIR_Legendary:
		ActiveStars[1] = ActiveStars[2] = ActiveStars[3] = ActiveStars[4] = ActiveStars[5] = true;
		break;
	case EItemRarity::EIR_Max:
		break;
	default:
		break;
	}
}

void AItem::SetItemProperties(EItemState State)
{
	switch (State)
	{
		case EItemState::EIS_Pickup:

			ItemMesh->SetSimulatePhysics(false);
			ItemMesh->SetVisibility(true);
			ItemMesh->SetEnableGravity(false);
			ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
			//AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

			CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
			CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			break;

		case EItemState::EIS_Equipped:

			PickupWidget->SetVisibility(false);
			ItemMesh->SetSimulatePhysics(false);
			ItemMesh->SetVisibility(true);
			ItemMesh->SetEnableGravity(false);
			ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);


			CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		break;


		case EItemState::EIS_Falling:

			ItemMesh->SetSimulatePhysics(true);
			ItemMesh->SetVisibility(true);
			ItemMesh->SetEnableGravity(true);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);


			CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			break;

		case EItemState::EIS_EquipInterping:

			PickupWidget->SetVisibility(false);
			ItemMesh->SetSimulatePhysics(false);
			ItemMesh->SetVisibility(true);
			ItemMesh->SetEnableGravity(false);
			ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);


			CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
	}
}

void AItem::StartItemCurve(AShooterCharacter* Char)
{
	CharacterRef = Char;
	ItemInterpStartLocation = GetActorLocation();
	bInterping = true;

	SetItemState(EItemState::EIS_EquipInterping);

	GetWorldTimerManager().SetTimer(ItemInterpTimer, this, &AItem::FinishInterping, ZCurveTime);

	const float CameraRotationYaw{ CharacterRef->GetFollowCamera()->GetComponentRotation().Yaw };
	const float ItemRotationYaw{ GetActorRotation().Yaw };

	InterpInitialYawOffset = ItemRotationYaw - CameraRotationYaw;

}

void AItem::FinishInterping()
{
	bInterping = false;
	if (CharacterRef)
	{
		
		CharacterRef->GetPickupItem(this);

	}
	SetActorScale3D(FVector(1.f));
}

void AItem::ItemInterp(float DeltaTime)
{
	if (!bInterping) return;

	if (CharacterRef && ItemZCurve)
	{
		const float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(ItemInterpTimer);
		const float CurveValue = ItemZCurve->GetFloatValue(ElapsedTime);

		FVector ItemLocation{ ItemInterpStartLocation };
		const FVector CameraInterpLocation{ CharacterRef->GetCameraInterpLocation() };

		const FVector ItemToCameraVector{ 0.f,0.f,(CameraInterpLocation - ItemLocation).Z };
		const float DeltaZ = ItemToCameraVector.Size();

		const FVector CurrentLocation{ GetActorLocation() };

		const float InterpXValue = FMath::FInterpTo(CurrentLocation.X, CameraInterpLocation.X, DeltaTime, 30.f);
		const float InterpYValue = FMath::FInterpTo(CurrentLocation.Y, CameraInterpLocation.Y, DeltaTime, 30.f);

		ItemLocation.X = InterpXValue;
		ItemLocation.Y = InterpYValue;

		ItemLocation.Z += CurveValue * DeltaZ;

		SetActorLocation(ItemLocation, true, nullptr, ETeleportType::TeleportPhysics);

		const FRotator CameraRotation{ CharacterRef->GetFollowCamera()->GetComponentRotation().Yaw };
		FRotator ItemRotation{ 0.f ,CameraRotation.Yaw + InterpInitialYawOffset , 0.f };

		SetActorRotation(ItemRotation, ETeleportType::TeleportPhysics);

		if (ItemScaleCurve)
		{
			const float ScaleCurveValue = ItemScaleCurve->GetFloatValue(ElapsedTime);
			SetActorScale3D(FVector(ScaleCurveValue, ScaleCurveValue, ScaleCurveValue));
		}
		

	}
}

void AItem::SetItemState(EItemState State)
{
	ItemState = State;
	SetItemProperties(State);
}
