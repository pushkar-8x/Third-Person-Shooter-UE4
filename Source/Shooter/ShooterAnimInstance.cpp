// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UShooterAnimInstance::UShooterAnimInstance() :
	speed(0.f), bIsInAir(false), bIsAccelerating(false), bAiming(false), MovementOffsetYaw(0.f), LastMovementOffsetYaw(0.f),
	TIPCharacterYaw(0.f), TIPCharacterYawlastFrame(0.f),
	CharacterRotation(FRotator(0.f)), CharacterRotationLastFrame(FRotator(0.f)), YawDelta(0.f),
	RootYawOffset(0.f), Pitch(0.f), bReloading(false), OffsetState(EOffsetState::EOS_Hip),
	RecoilWeight(1.0f),bTurningInPlace(false)
{
}

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	if (ShooterCharacter)
	{	
		bCrouching = ShooterCharacter->GetCrouching();

		bReloading = ShooterCharacter->GetCombatState() == ECombatState::ECS_Reloading;

		FVector velocity{ ShooterCharacter->GetVelocity() };
		velocity.Z = 0;

		speed = velocity.Size();

		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		

		FRotator MovementRotation = UKismetMathLibrary:: MakeRotFromX( ShooterCharacter->GetVelocity());

		

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation , AimRotation).Yaw;

		if (ShooterCharacter->GetVelocity().Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}

		bAiming = ShooterCharacter->GetAiming();

		if (bReloading) OffsetState = EOffsetState::EOS_Reloading;
		else if (bIsInAir) OffsetState = EOffsetState::EOS_InAir;
		else if (bAiming) OffsetState = EOffsetState::EOS_Aiming;
		else OffsetState = EOffsetState::EOS_Hip;

		
	}

	TurnInPlace();
	Lean(DeltaTime);
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

void UShooterAnimInstance::TurnInPlace()
{
	if (ShooterCharacter == nullptr) return;

	Pitch = ShooterCharacter->GetBaseAimRotation().Pitch;

	if (speed > 0 || bIsInAir)
	{
		RootYawOffset = 0.f;
		TIPCharacterYaw = ShooterCharacter->GetActorRotation().Yaw;
		TIPCharacterYawlastFrame = TIPCharacterYaw;
		RotationCurveLastFrame = 0.f;
		RotationCurve = 0.f;
	}
	else
	{
		TIPCharacterYawlastFrame = TIPCharacterYaw;
		TIPCharacterYaw = ShooterCharacter->GetActorRotation().Yaw;

		const float TIPYawDelta{ TIPCharacterYaw - TIPCharacterYawlastFrame };

		RootYawOffset = UKismetMathLibrary::NormalizeAxis(RootYawOffset - TIPYawDelta);

		const float Turning{ GetCurveValue(TEXT("Turning")) };

		if (Turning > 0)
		{
			bTurningInPlace = true;
			RotationCurveLastFrame = RotationCurve;
			RotationCurve = GetCurveValue(TEXT("Rotation"));

			const float DeltaRotation{ RotationCurve - RotationCurveLastFrame };

			RootYawOffset > 0 ? RootYawOffset -= DeltaRotation : RootYawOffset += DeltaRotation;

			const float AbsRootYawOffset{ FMath::Abs(RootYawOffset) };

			if (AbsRootYawOffset > 90.f)
			{
				const float YawExcess{ AbsRootYawOffset - 90.f };

				RootYawOffset > 0 ? RootYawOffset -= YawExcess : RootYawOffset += YawExcess;
			}
		}
		else
		{
			bTurningInPlace = false;

		}

		


		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(1, -1, FColor::Blue, FString::Printf(TEXT("CharacterYaw : %f"), CharacterYaw));

			//GEngine->AddOnScreenDebugMessage(2, -1, FColor::Red, FString::Printf(TEXT("RootOffsetYaw : %f"), RootYawOffset));
		}
	}

	if (bTurningInPlace)
	{
		if (bReloading)
		{
			RecoilWeight = 1.f;
		}
		else
		{
			RecoilWeight = 0.f;
		}

	}
	else
	{
		if (bCrouching)
		{
			if (bReloading)
			{
				RecoilWeight = 1.f;
			}
			else
			{
				RecoilWeight = 0.1f;
			}
		}
		else
		{
			if (bAiming || bReloading)
			{
				RecoilWeight = 1.f;
			}
			else
			{
				RecoilWeight = 0.5f;
			}
		}
	}

}

void UShooterAnimInstance::Lean(float DeltaTime)
{
	if (ShooterCharacter == nullptr) return;

	CharacterRotationLastFrame = CharacterRotation;

	CharacterRotation = ShooterCharacter->GetActorRotation();

	const FRotator Delta{ UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation , CharacterRotationLastFrame) };

	const float Target{ (Delta.Yaw) / DeltaTime };

	const float Interp{ FMath::FInterpTo(YawDelta , Target , DeltaTime , 6.f) };

	YawDelta = FMath::Clamp(Interp, -90.f, 90.f);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, -1, FColor::Blue, FString::Printf(TEXT("YawDelta : %f"), YawDelta));

		GEngine->AddOnScreenDebugMessage(2, -1, FColor::Green, FString::Printf(TEXT("Delta.Yaw : %f"), Delta.Yaw));
	}
}
