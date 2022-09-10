// Fill out your copyright notice in the Description page of Project Settings.


#include "RussianGun.h"

ARussianGun::ARussianGun(const FObjectInitializer& ObjectInitializer)
{
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponSceneComponent"));
	}
	if(!WeaponMeshComponent)
	{
		WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/FPS_Weapon_Bundle/Weapons/Meshes/KA_Val/SM_KA_Val_X.SM_KA_Val_X'"));
		if (Mesh.Succeeded())
		{
			WeaponMeshComponent->SetStaticMesh(Mesh.Object);
		}
		RootComponent = WeaponMeshComponent;
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/FPS_Weapon_Bundle/Weapons/Materials/KA_Val/M_KA_Val.M_KA_Val'"));
	if (Material.Succeeded())
	{
		WeaponMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, WeaponMeshComponent);
	}
	WeaponMeshComponent->SetMaterial(0, WeaponMaterialInstance);
	WeaponMeshComponent->SetSimulatePhysics(false);
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!WeaponActivationRange)
	{
		WeaponActivationRange = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponActivationRange"));
		WeaponActivationRange->InitBoxExtent({ 60.0f, 10.0f, 10.0f });
		WeaponActivationRange->SetupAttachment(RootComponent);
		WeaponActivationRange->SetGenerateOverlapEvents(true);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>FiredSound(TEXT("'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
	if (FiredSound.Succeeded())
	{
		SoundCue = FiredSound.Object;
	}

	maxMagCapacity = 25;
	currentMagCapacity = 25;
	totalAmmoLeft = 25;
}

void ARussianGun::Fire(FVector MuzzleOffset, UEquipment* PlayerEquipment, const FVector& playerLocationAtShooting)
{
		//where the player is looking
		FVector CameraLocation{this->GetActorLocation()};
		FRotator CameraRotator{this->GetActorRotation()};
		//GetActorEyesViewPoint(CameraLocation, CameraRotator);

		//transforming MuzzleOffset from camera space to world space (probably rotating offset so it will match world's XYZ
		FVector MuzzleLocation = this->GetActorLocation() + FTransform(CameraRotator).TransformVector(MuzzleOffset);

		//making the aim facing slightly upwards
		FRotator MuzzleRotation = this->GetActorRotation();
		//MuzzleRotation.Pitch += 10.0f;

		//getting and checking if the world exists
		UWorld* World = GetWorld();
		if (World && currentMagCapacity!=0)
		{
			//struct with spawn parameters data
			FActorSpawnParameters SpawnParameters;
			//TPCharacter is the spawning actor
			SpawnParameters.Owner = this;
			//setting bullet's APawn responsible for damage
			SpawnParameters.Instigator = GetInstigator();

			//spawning a bullet
			ARussianBullet* Bullet = World->SpawnActor<ARussianBullet>(MuzzleLocation, MuzzleRotation, SpawnParameters);
			//if bullet exists
			if (Bullet)
			{
				UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, SoundCue, Bullet->GetActorLocation(), FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
				FVector LaunchDirection = MuzzleRotation.Vector();
				Bullet->FireInDirection(LaunchDirection, playerLocationAtShooting);
				--currentMagCapacity;
			}
		}

}
void ARussianGun::Reload(UEquipment* PlayerEquipment)
{
	int howMuchToReload{ maxMagCapacity - currentMagCapacity };
	if (PlayerEquipment->getTotalAmmo556() >= howMuchToReload)
	{
		currentMagCapacity += howMuchToReload;
		PlayerEquipment->substractTotalAmmo556(howMuchToReload);
	}
	else
	{
		int ammoLeft{ PlayerEquipment->getTotalAmmo556() };
		currentMagCapacity += ammoLeft;
		PlayerEquipment->substractTotalAmmo556(ammoLeft);
	}
}
void ARussianGun::getTotalAmmo(UEquipment* PlayerEquipment)
{
	totalAmmoLeft = PlayerEquipment->getTotalAmmo556();
};


