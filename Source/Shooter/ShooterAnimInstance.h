// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"

/**
 * 
 */

UENUM(BluePrintType)

enum class EOffsetState:uint8
{
	EOS_Reloading UMETA(DisplayName = "Reloading"),
	EOS_Aiming UMETA(DisplayName = "Aiming"),
	EOS_Hip UMETA(DisplayName = "Hip"),
	EOS_InAir UMETA(DisplayName = "InAir"),
	EOS_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class SHOOTER_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		

public:
	UShooterAnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);
	virtual void NativeInitializeAnimation() override;

protected:

	void TurnInPlace();
	void Lean(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
	class AShooterCharacter* ShooterCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
	float speed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
	bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = true))
	bool bAiming;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Movement, meta = (AllowPrivateAccess = true))
	float MovementOffsetYaw;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Movement, meta = (AllowPrivateAccess = true))
	float LastMovementOffsetYaw;

	float TIPCharacterYaw;

	float TIPCharacterYawlastFrame;


	FRotator CharacterRotation;

	FRotator CharacterRotationLastFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	float YawDelta;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	bool bCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	float RootYawOffset;

	float RotationCurve;

	float RotationCurveLastFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	float Pitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	bool bReloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float RecoilWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bTurningInPlace;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	EOffsetState OffsetState;


};
