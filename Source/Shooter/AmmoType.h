#pragma once

UENUM(BlueprintType)

enum class EAmmoType : uint8
{
	ET_9MM UMETA(DisplayName = "9mm"),
	ET_AR UMETA(DisplayName = "AssaultRifle"),

	EAT_MAX UMETA(DisplayName = "DefaultMax")

};