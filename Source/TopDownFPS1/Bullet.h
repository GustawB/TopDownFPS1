// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Target_Shield.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TopDownFPS1GameModeBase.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOPDOWNFPS1_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	//virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class UBoxComponent* BulletCollisionComponent; //using class because of en error

	UPROPERTY(VisibleAnywhere, Category = BulletMovement)
		class UProjectileMovementComponent* BulletMovementComponent; //using class because of en error

	void FireInDirection(const FVector& ShootDirection, const FVector& playerLocationAtShooting);

	//bullet's mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* BulletMeshComponent;
	//bullet's material
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* BulletMaterialInstance;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* BulletHoleMaterialInstance;

	//Function called when the bullet hits something
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
		ADecalActor* BulletHole;

	//location of a hit passed to the shield
	UPROPERTY()
		FVector HitLocationForShield {};

	UFUNCTION()
		void WeaponParameters(double InitialSpeed, double MaximumSpeed, const FString& WeaponType);

	UFUNCTION()
		virtual double BulletSpeed();

	UFUNCTION()
		virtual double BulletGravity();

	UFUNCTION()
		int setMultiplayer(float distance);

	UPROPERTY()
		FVector playerLocationAtShootingInBCPP {};

	double InitSpeed{};
	double MaxSpeed{};
	FString WeaponName{};

};