// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Item.h"
#include "AmmoType.h"
#include "ShooterCharacter.generated.h"



UENUM(BlueprintType)

enum class ECombatState : uint8
{
	ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECS_FireTimerInProgress UMETA(DisplayName = "FireTimeInProgress"),
	ECS_Reloading UMETA(DisplayName = "Reloading"),
	ECS_Max UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Jump() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void Turn(float Value);
	void LookUp(float Value);

	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

	void OnAimButtonPressed();
	void OnAimButtonReleased();

	void Aim();

	void StopAiming();

	void CameraInterpZoom(float DeltaTime);

	void SetLookRates();

	void CalculateCrosshairSpread(float DeltaTime);

	void StartCrosshairBulletFire();

	void StopCrossHairBulletFire();

	void FireButtonPressed();
	void FireButtonReleased();

	void StartFireTimer();

	UFUNCTION()
	void AutoFireReset();
	
	bool TraceUnderCrosshairs(FHitResult& OutHitResult , FVector& OutBeamLocation);

	void TraceForItems();

	class AWeapon* SpawnDefaultWeapon();

	void EquipWeapon(AWeapon* WeaponToEquip);

	void DropWeapon();

	void SwapWeapon(AWeapon* WeaponToSwap);

	void OnSelectButtonPressed();
	void OnSelectButtonReleased();

	
	void InitializeAmmoMap();

	bool WeaponHasAmmo();

	void PlayFireSound();

	void SendBullet();

	void PlayGunFireMontage();

	void ReloadButtonPressed();

	void ReloadWeapon();

	bool CarryingAmmo();

	void CrouchButtonPressed();

	void InterpCapsuleHalfHeight(float DeltaTime);

	void PickupAmmo(class AAmmo* Ammo);

	UFUNCTION(BlueprintCallable)
		void GrabClip();

	UFUNCTION(BluePrintCallable)
		void ReleaseClip();



	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetCameraInterpLocation();

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		float BaseMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		float CrouchMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		float AimMovementSpeed;

	bool bAimButtonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		float BaseFriction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
		float CrouchFriction;


	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	float StandingCapsuleHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
		float CrouchingCapsuleHalfHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	float HipTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	float HipLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	float AimingTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	float AimingLookUpRate;

	//Mouse Turn rates-----

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = true) , meta = (ClampMin = "0.0" , ClampMax="1.0" , UIMin="0.0",UIMax = "1.0"))
		float MouseHipTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true),
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MouseHipLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true)
		, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MouseAimingTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true)
		, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float MouseAimingLookUpRate;



	UPROPERTY(EditAnywhere , BluePrintReadWrite , Category = Combat , meta = (AllowPrivateAccess = true))
	class USoundCue* FireSound = NULL;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Combat, meta = (AllowPrivateAccess = true))
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Combat, meta = (AllowPrivateAccess = true))
	class UParticleSystem* BeamParticles;


	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Combat, meta = (AllowPrivateAccess = true))
	class UAnimMontage* HipFireMontage;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Combat, meta = (AllowPrivateAccess = true))
	class UParticleSystem* ImpactParticles;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	bool bCrouching;

	float CameraDefaultFOV;
	float CameraZoomedFOV;
	float CameraCurrentFOV;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Combat, meta = (AllowPrivateAccess = true))
	float ZoomInterpSpeed;

	
	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	float CrosshairSpreadMultiplier;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	float CrosshairVelocityFactor;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	float CrosshairInAirFactor;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	float CrosshairAimFactor;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = Combat, meta = (AllowPrivateAccess = true))
	float CrosshairShootingFactor;


	bool bFireButtonPressed;
	bool bShouldFire;

	float AutomaticFireRate;
	FTimerHandle AutoFireTimer;

	float ShootTimeDuration;
	bool bFiringBullet;
	FTimerHandle CrosshairShootTimer;

	bool bShouldTraceForItems;

	int8 OverlappedItemCount;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	class AItem* TraceHitItemLastFrame;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	class AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	AItem* TraceHitItem;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	float CameraInterpDistance;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	float CameraInterpElevation;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	class UCurveFloat* ItemZCurve;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	TMap<EAmmoType, int32> AmmoMap;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	int32 Starting9mmAmmo;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	int32 StartingARAmmo;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	ECombatState CombatState;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Combat, meta = (AllowPrivateAccess = true))
	UAnimMontage* ReloadMontage;

	UFUNCTION(BluePrintCallable)
	void FinishReloading();

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	FTransform ClipTransform;

	UPROPERTY(VisibleAnyWhere, BluePrintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	USceneComponent* HandSceneComponent;

public :
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool GetAiming() const { return bIsAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrossHairSpreadMultiplier() const;

	FORCEINLINE int8 GetOverlappedItemCount() const { return OverlappedItemCount; }

	void UpdateOverlappedItemCount(int8 Amount);

	void GetPickupItem(AItem* Item);

	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }

	FORCEINLINE bool GetCrouching() const { return bCrouching; }

};
