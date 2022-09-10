// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "BaseWeapon.h"
#include "RussianGun.h"
#include "TimeGameActivator.h"
#include "LimitedGameActivator.h"
#include "Ammo762.h"
#include "Ammo556.h"
#include "Equipment.h"
#include "TimerManager.h"
#include "Kalasnikow.h"
#include "KalasnikowBullet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

UCLASS()
class TOPDOWNFPS1_API ATPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//bullet class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Bullet)
		TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = Bullet)
		TSubclassOf<class AKalasnikowBullet> KalasnikowBulletClass;

	//weapon class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TSubclassOf<class ABaseWeapon> WeaponClass;

private:

	UPROPERTY()
		float SpeedMultiplayer;

	UPROPERTY()
		FVector WeaponLocation;

	UPROPERTY()
		FRotator WeaponRotation;

	UPROPERTY()
		bool canHandsBeVisible;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//functions responsible for moving
	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();


	//a camera for the character
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* TPCameraComponent;

	UFUNCTION()
		void Fire();

	UFUNCTION()
		void StartSprint();

	UFUNCTION()
		void StopSprint();

	UFUNCTION()
		void StartFire();

	UFUNCTION()
		void StopFire();

	UFUNCTION()
		void PickUp();

	UFUNCTION()
		void Reload();

	UFUNCTION()
		void StartAiming();

	UFUNCTION()
		void StopAiming();

	UPROPERTY()
		FTimerHandle WeaponTimer;

	UPROPERTY()
		float TimeBetweenShots;

	//Muzzle offset from camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		FVector MuzzleOffset;

	//FPS mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Hands_Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Aiming_Hands_Mesh;


	//a range of weapon pick up
	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent* WeaponPickUpRange;

	//a pointer to the current weapon used to destroy that weapon when the new one is equipped
	UPROPERTY(BlueprintReadOnly)
		ABaseWeapon* WeaponToDestroy;

	//destroys current weapon if player equips a new one
	UFUNCTION()
		void DestroyWeapon(ABaseWeapon* Weapon);
	
	UFUNCTION()
		void SpawnRussianGun(UWorld* World);

	UFUNCTION()
		void SpawnKalasnikow(UWorld* World);

	UPROPERTY(BlueprintReadOnly)
		FString WeaponName{};

	UPROPERTY()
		AKalasnikow* Kalasnikow;

	UPROPERTY()
		UEquipment* PlayerEquipment;

	UPROPERTY(BlueprintReadWrite)
		bool GameState;

};

