// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemRarity:uint8
{
	EIR_Damaged UMETA(DisplayName = "Damaged"),
	EIR_Common UMETA(DisplayName = "Common"),
	EIR_Uncommon UMETA(DisplayName = "Uncommon"),
	EIR_Rare UMETA(DisplayName = "Rare"),
	EIR_Legendary UMETA(DisplayName = "Legendary"),

	EIR_Max UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EItemState :uint8
{
	EIS_Pickup UMETA(DisplayName = "Pickup"),
	EIS_EquipInterping UMETA(DisplayName = "EquipInterping"),
	EIS_PickedUp UMETA(DisplayName = "PickedUp"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Falling UMETA(DisplayName = "Falling")

	
};

UCLASS()
class SHOOTER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	virtual void EnableCustomDepth();
	virtual void DisableCustomDepth();
	virtual void InitializeCustomDepth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetActiveStars();

	virtual void SetItemProperties(EItemState State);

	virtual void OnConstruction(const FTransform& Transform);

	void FinishInterping();

	void ItemInterp(float DeltaTime);

	void ResetPulseTimer();
	void StartPulseTimer();

	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void EnableGlowMaterial();
	void DisableGlowMaterial();

private :

	UPROPERTY(VisibleAnywhere,BluePrintReadOnly , Category = "Item Properties" , meta = (AllowPrivateAccess =  "true"))
	USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* PickupWidget;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AreaSphere;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	int32 ItemCount;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	EItemRarity ItemRarity;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	TArray<bool> ActiveStars;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	EItemState ItemState;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	FVector ItemInterpStartLocation;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	FVector CameraTargetLocation;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	bool bInterping;

	FTimerHandle ItemInterpTimer;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	float ZCurveTime;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class UCurveFloat* ItemZCurve;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class AShooterCharacter* CharacterRef;

	float InterpInitialYawOffset;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* ItemScaleCurve;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class USoundCue* PickupSound;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	USoundCue* EquipSound;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		int32 MaterialIndex;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		UMaterialInstance* MaterialInstance;

	bool bCanChangeCustomDepth;


	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class UCurveVector* PulseCurve;

	FTimerHandle PulseTimer ;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		float PulseCurveTime;

	UPROPERTY(VisibleAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		float GlowAmount;

	UPROPERTY(VisibleAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		float FresnelExponent;

	UPROPERTY(VisibleAnywhere, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		float FresnelReflectFraction;

	

	void UpdatePulse();


public :

	
	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }
	
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }
	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }
	FORCEINLINE EItemState GetItemState() const { return ItemState; }
	FORCEINLINE USkeletalMeshComponent* GetItemMesh() const { return ItemMesh; }
	void SetItemState(EItemState State);
	void StartItemCurve(AShooterCharacter* Char);

	FORCEINLINE USoundCue* GetPickupSound() const { return PickupSound; }
	FORCEINLINE USoundCue* GetEquipSound() const { return EquipSound; }

	FORCEINLINE int32 GetItemCount() const { return ItemCount; }

};
