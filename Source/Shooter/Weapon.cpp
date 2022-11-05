// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Engine/SkeletalMeshSocket.h"


AWeapon::AWeapon() :
	ThrowWeaponTime(0.7f), bFalling(false), AmmoCount(30), MagazineCapacity(30),
	WeaponType(EWeaponType::EWT_SubmachineGun), AmmoType(EAmmoType::ET_9MM),
	ReloadMontageName(FName(TEXT("Reload SMG"))), ClipBoneName(TEXT("smg_clip" ))

{
	PrimaryActorTick.bCanEverTick = true;

	
	
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetItemState() == EItemState::EIS_Falling && bFalling)
	{
		const FRotator MeshRotation{ 0.f, GetItemMesh()->GetComponentRotation().Yaw,0.f };

		GetItemMesh()->SetWorldRotation(MeshRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

void AWeapon::ThrowWeapon()
{
	FRotator MeshRotation{ 0.f , GetItemMesh()->GetComponentRotation().Yaw , 0.f };
	GetItemMesh()->SetWorldRotation(MeshRotation, false, nullptr, ETeleportType::TeleportPhysics);

	const FVector MeshForward{ GetItemMesh()->GetForwardVector() };
	const FVector MeshRight{ GetItemMesh()->GetRightVector() };

	FVector ImpulseDirection = MeshRight.RotateAngleAxis(-20.f, MeshForward);

	float RandomRotation{ 30.f };
	ImpulseDirection = ImpulseDirection.RotateAngleAxis(RandomRotation, FVector(0.f, 0.f, 1.f));
	ImpulseDirection *= 2000.f;

	GetItemMesh()->AddImpulse(ImpulseDirection);

	bFalling = true;

	GetWorldTimerManager().SetTimer(ThrowWeaponTimer, this, &AWeapon::StopFalling, ThrowWeaponTime);


}

void AWeapon::DecrementAmmo()
{
	if (AmmoCount - 1 < 0)
	{
		AmmoCount = 0;
	}
	else
	{
		--AmmoCount;
	}
}

void AWeapon::ReloadAmmo(int32 Amount)
{
	checkf(AmmoCount + Amount <= MagazineCapacity, TEXT("Attempted to reload with more than mag capacity"));
	AmmoCount += Amount;
}



void AWeapon::StopFalling()
{
	bFalling = false;
	SetItemState(EItemState::EIS_Pickup);
}
