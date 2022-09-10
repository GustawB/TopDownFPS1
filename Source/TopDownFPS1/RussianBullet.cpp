// Fill out your copyright notice in the Description page of Project Settings.


#include "RussianBullet.h"

ARussianBullet::ARussianBullet(const FObjectInitializer& ObjectInitializer)
{
	//setting bullet's material
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Blueprints/Materials/SphereMaterial.SphereMaterial'"));
	if (Material.Succeeded())
	{
		BulletMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, BulletMeshComponent);
	}
	BulletMeshComponent->SetMaterial(0, BulletMaterialInstance);
	BulletMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	BulletMeshComponent->SetupAttachment(RootComponent);

	BulletMovementComponent->InitialSpeed = Speed;
	BulletMovementComponent->MaxSpeed = Speed;
	BulletMovementComponent->ProjectileGravityScale = Gravity;
}

double ARussianBullet::BulletSpeed()
{
	return 300.0f;
}

double ARussianBullet::BulletGravity()
{
	return 0.3f;
}

