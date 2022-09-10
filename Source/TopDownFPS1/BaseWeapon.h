// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Bullet.h"
#include "Equipment.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseWeapon.generated.h"

UCLASS()
class TOPDOWNFPS1_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = Bullet)
		//TSubclassOf<class ABullet> BulletClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		UMaterialInstanceDynamic* WeaponMaterialInstance;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		UBoxComponent* WeaponCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent* WeaponActivationRange;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* AimingCameraComponent;
	
	UFUNCTION()
		virtual void Fire(FVector MuzzleOffset, UEquipment* PlayerEquipment, const FVector& playerLocationAtShooting);

	UPROPERTY(BlueprintReadOnly)
		int maxMagCapacity;

	UPROPERTY(BlueprintReadOnly)
		int currentMagCapacity;

	UPROPERTY(BlueprintReadOnly)
		int totalAmmoLeft;

	UFUNCTION()
		int getMaxMagCapacity();

	UFUNCTION()
		int getCurrentMagCapacity();

	UFUNCTION(BlueprintCallable)
		virtual void getTotalAmmo(UEquipment* PlayerEquipment);

	UFUNCTION()
		virtual void Reload(UEquipment* PlayerEquipment);

	UPROPERTY()
		USoundCue* SoundCue;

};
