// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"


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

public :
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool GetAiming() const { return bIsAiming; }

	UFUNCTION(BlueprintCallable)
	float GetCrossHairSpreadMultiplier() const;

	FORCEINLINE int8 GetOverlappedItemCount() const { return OverlappedItemCount; }

	void UpdateOverlappedItemCount(int8 Amount);

	void GetPickupItem(AItem* Item);

};
