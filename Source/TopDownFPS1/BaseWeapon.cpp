// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponSceneComponent"));
	}
	if (!WeaponMeshComponent)
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
	*/
	if (!AimingCameraComponent)
	{
		AimingCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("AimingCameraComponent"));
		AimingCameraComponent->SetupAttachment(WeaponMeshComponent);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue>FiredSound(TEXT("'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));
	if (FiredSound.Succeeded())
	{
		SoundCue = FiredSound.Object;
	}
	
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 void ABaseWeapon::Fire(FVector MuzzleOffset, UEquipment* PlayerEquipment, const FVector& playerLocationAtShooting)
{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BaseWeapon"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("FIRE"));
		//where the player is looking
		FVector CameraLocation;
		FRotator CameraRotator;
		GetActorEyesViewPoint(CameraLocation, CameraRotator);

		//transforming MuzzleOffset from camera space to world space (probably rotating offset so it will match world's XYZ
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotator).TransformVector(MuzzleOffset);

		//making the aim facing slightly upwards
		FRotator MuzzleRotation = CameraRotator;
		MuzzleRotation.Pitch += 10.0f;

		//getting and checking if the world exists
		UWorld* World = GetWorld();
		if (World)
		{
			//struct with spawn parameters data
			FActorSpawnParameters SpawnParameters;
			//TPCharacter is the spawning actor
			SpawnParameters.Owner = this;
			//setting bullet's APawn responsible for damage
			SpawnParameters.Instigator = GetInstigator();

			//spawning a bullet
			ABullet* Bullet = World->SpawnActor<ABullet>(MuzzleLocation, MuzzleRotation, SpawnParameters);
			//if bullet exists
			if (Bullet)
			{
				//spawning sound
				UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, SoundCue, Bullet->GetActorLocation(), FRotator::ZeroRotator, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Working"));
				//initial trajectory of the bullet
				FVector LaunchDirection = MuzzleRotation.Vector();
				Bullet->FireInDirection(LaunchDirection, playerLocationAtShooting);
			}
		}

}

 int ABaseWeapon::getMaxMagCapacity()
 {
	 return maxMagCapacity;
 }

 int ABaseWeapon::getCurrentMagCapacity()
 {
	 return currentMagCapacity;
 }

 void ABaseWeapon::getTotalAmmo(UEquipment* PlayerEquipment)
 {
 }

 void ABaseWeapon::Reload(UEquipment* PlayerEquipment)
 {
 }

