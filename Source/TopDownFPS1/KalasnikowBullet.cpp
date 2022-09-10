// Fill out your copyright notice in the Description page of Project Settings.


#include "KalasnikowBullet.h"

AKalasnikowBullet::AKalasnikowBullet(const FObjectInitializer& ObjectInitializer)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("KalasnikowBullet"));
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Blueprints/Materials/SphereMaterial1.SphereMaterial1'"));
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


