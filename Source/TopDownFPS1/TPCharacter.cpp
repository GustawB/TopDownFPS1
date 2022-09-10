// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCharacter.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponName = "";

	TPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPCamera"));
	check(TPCameraComponent != nullptr);
	TPCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	TPCameraComponent->SetRelativeLocation(FVector(-20.0f, 0.0f, 50.0f + BaseEyeHeight));

	Hands_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands_Mesh"));
	Aiming_Hands_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Aiming_Hands_Mesh"));
	check(Hands_Mesh != nullptr);
	check(Aiming_Hands_Mesh != nullptr);

	Hands_Mesh->SetOnlyOwnerSee(true);
	Aiming_Hands_Mesh->SetOnlyOwnerSee(true);

	//attaching fps mesh to camera
	Hands_Mesh->SetupAttachment(TPCameraComponent);
	Aiming_Hands_Mesh->SetupAttachment(TPCameraComponent);

	//disable some shadows so we have an illusuion of one mesh
	Hands_Mesh->bCastDynamicShadow = false;
	Aiming_Hands_Mesh->bCastDynamicShadow = false;
	Hands_Mesh->CastShadow = false;
	Aiming_Hands_Mesh->CastShadow = false;

	//owner can't see body's mesh
	GetMesh()->SetOwnerNoSee(true);

	if (!WeaponPickUpRange)
	{
		WeaponPickUpRange = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponPickUpRange"));
		WeaponPickUpRange->InitBoxExtent({ 100.0f, 10.0f, 10.0f });
		WeaponPickUpRange->SetGenerateOverlapEvents(true);
	}
	WeaponPickUpRange->SetupAttachment(TPCameraComponent);
	WeaponToDestroy = nullptr;

	if (!PlayerEquipment)
		PlayerEquipment = CreateDefaultSubobject<UEquipment>(TEXT("PlayerEquipment"));

	TimeBetweenShots = 1.0f;
	SpeedMultiplayer = 3.0f;
	canHandsBeVisible = true;
}
// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Aiming_Hands_Mesh->SetHiddenInGame(true);
	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TPCharacter"));

}

// Called every frame
void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if player isn't holding any weapons, he won't see his hands
	if (WeaponToDestroy != nullptr && canHandsBeVisible)
		Hands_Mesh->SetHiddenInGame(false);
	else
		Hands_Mesh->SetHiddenInGame(true);

	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%lld"), GetCharacterMovement()->MaxWalkSpeed));
}

// Called to bind functionality to input
void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ATPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ATPCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ATPCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATPCharacter::StopJump);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ATPCharacter::PickUp);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATPCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATPCharacter::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATPCharacter::Reload);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATPCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATPCharacter::StopSprint);
	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &ATPCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &ATPCharacter::StopAiming);
}

void ATPCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ATPCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ATPCharacter::StartJump()
{
	bPressedJump = true;
}

void ATPCharacter::StopJump()
{
	bPressedJump = false;
}

void ATPCharacter::Fire()
{
	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);
	FVector playerLocationAtShooting{ this->GetActorLocation() };
	if (WeaponToDestroy != nullptr)
		WeaponToDestroy->Fire(MuzzleOffset, PlayerEquipment, playerLocationAtShooting);
}

void ATPCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SpeedMultiplayer;
}

void ATPCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= SpeedMultiplayer;
}

void ATPCharacter::StartAiming()
{
	if (WeaponToDestroy != nullptr)
	{
		WeaponToDestroy->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		WeaponToDestroy->AttachToComponent(Aiming_Hands_Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName{ "Weapon_Socket" });
		Aiming_Hands_Mesh->SetHiddenInGame(false);
		canHandsBeVisible = false;
		//WeaponToDestroy->AimingCameraComponent->SetActive(true);
		//TPCameraComponent->SetActive(false);
		//Hands_Mesh->SetRelativeLocation()
	}
}

void ATPCharacter::StopAiming()
{
	if (WeaponToDestroy != nullptr)
	{
		Aiming_Hands_Mesh->SetHiddenInGame(true);
		canHandsBeVisible = true;
		WeaponToDestroy->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		WeaponToDestroy->AttachToComponent(Hands_Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName{ "Weapon_Socket" });
		//WeaponToDestroy->AimingCameraComponent->SetActive(false);
		//TPCameraComponent->SetActive(true);
	}
}

void ATPCharacter::StartFire()
{
	Fire();

	if (AKalasnikow* K = Cast<AKalasnikow>(WeaponToDestroy))
		TimeBetweenShots = 0.15f;
	else if (ARussianGun* R = Cast<ARussianGun>(WeaponToDestroy))
		TimeBetweenShots = 0.30f;
	GetWorldTimerManager().SetTimer(WeaponTimer, this, &ATPCharacter::Fire, TimeBetweenShots ,true);
}

void ATPCharacter::StopFire()
{
	GetWorldTimerManager().ClearTimer(WeaponTimer);
}

void ATPCharacter::DestroyWeapon(ABaseWeapon* Weapon)
{
	if (WeaponToDestroy != nullptr)
		WeaponToDestroy->Destroy();
	WeaponToDestroy = Weapon;
}

void ATPCharacter::SpawnRussianGun(UWorld* World)
{
	ARussianGun* Weapon = Cast<ARussianGun>(WeaponToDestroy);
	if (Weapon == nullptr)
	{
		Weapon = World->SpawnActor<ARussianGun>(ARussianGun::StaticClass());
		if (Weapon)
		{
			WeaponName = "RussianGun";
			DestroyWeapon(Weapon);
			Weapon->AttachToComponent(Hands_Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName{ "Weapon_Socket" });
		}
	}
}

void ATPCharacter::SpawnKalasnikow(UWorld* World)
{	
	AKalasnikow* Weapon = Cast<AKalasnikow>(WeaponToDestroy);
	if (Weapon == nullptr)
	{
		Weapon = World->SpawnActor<AKalasnikow>(AKalasnikow::StaticClass());
		if (Weapon)
		{
			Kalasnikow = Weapon;
			WeaponName = "Kalasnikow";
			DestroyWeapon(Weapon);
			Weapon->AttachToComponent(Hands_Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName{ "Weapon_Socket" });
		}
	}
}

void ATPCharacter::PickUp()
{
	FVector PlayerLocation{ this->GetActorLocation() };
	UWorld* World = GetWorld();
	if (World)
	{
		TArray<AActor*> WeaponsInRange;
		WeaponPickUpRange->GetOverlappingActors(WeaponsInRange);
		for (int i{ 0 }; i < WeaponsInRange.Num(); ++i)
		{
			ARussianGun* RGWeapon = Cast<ARussianGun>(WeaponsInRange[i]);
			AKalasnikow* AKWeapon = Cast<AKalasnikow>(WeaponsInRange[i]);
			AAmmo556* A556 = Cast<AAmmo556>(WeaponsInRange[i]);
			AAmmo762* A762 = Cast<AAmmo762>(WeaponsInRange[i]);
			ATimeGameActivator* TimeGameActivator = Cast<ATimeGameActivator>(WeaponsInRange[i]);
			ALimitedGameActivator* LimitedGameActivator = Cast<ALimitedGameActivator>(WeaponsInRange[i]);
			if (A556)
			{
				PlayerEquipment->addTotalAmmo556(25);
				if(WeaponToDestroy != nullptr)
					WeaponToDestroy->getTotalAmmo(PlayerEquipment);
			}
			else if (A762)
			{
				PlayerEquipment->addTotalAmmo762(30);
				if (WeaponToDestroy != nullptr)
					WeaponToDestroy->getTotalAmmo(PlayerEquipment);
			}
			else if (RGWeapon)
			{
				SpawnRussianGun(World);
				WeaponToDestroy->getTotalAmmo(PlayerEquipment);
			}
			else if (AKWeapon)
			{
				SpawnKalasnikow(World);
				WeaponToDestroy->getTotalAmmo(PlayerEquipment);
			}
			else if (TimeGameActivator)
			{
				TimeGameActivator->isGameActivated = true;
			}
			else if (LimitedGameActivator)
			{
				LimitedGameActivator->isGameActivated = true;
				//GameState = true;
			}
		}
	}
}

void ATPCharacter::Reload()
{
	if (WeaponToDestroy != nullptr)
	{
		WeaponToDestroy->Reload(PlayerEquipment);
		WeaponToDestroy->getTotalAmmo(PlayerEquipment);
	}
	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Reload"));
}










