// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitSpeed = 0.0f;
	MaxSpeed = 0.0f;
	WeaponName = "";

	//creation of BoxComponent, and making it rootcomponent
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSceneComponent"));
	}
	if (!BulletCollisionComponent)
	{
		BulletCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BulletBoxComponent"));
		//Bullet's collision profile name is set here to "Bullet"
		BulletCollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));
		//Event called when component hits something, AddDynamic calls a function when hit happens
		BulletCollisionComponent->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
		BulletCollisionComponent->InitBoxExtent(FVector(20.0f, 10.0f, 10.0f));
		RootComponent = BulletCollisionComponent;

		if (!BulletMovementComponent)
		{
			BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementcomponent"));
			BulletMovementComponent->SetUpdatedComponent(BulletCollisionComponent);
			BulletMovementComponent->InitialSpeed = 3000.0f;
			BulletMovementComponent->MaxSpeed = 3000.0f;
			BulletMovementComponent->bShouldBounce = true;
			BulletMovementComponent->Bounciness = 0.3f;
			BulletMovementComponent->ProjectileGravityScale = 0.0f;
		}
		//BulletHole Material
		static ConstructorHelpers::FObjectFinder<UMaterial>BulletHoleMaterial(TEXT("'/Game/Blueprints/Materials/BulletHole.BulletHole'"));
		if (BulletHoleMaterial.Succeeded())
		{
			BulletHoleMaterialInstance = UMaterialInstanceDynamic::Create(BulletHoleMaterial.Object, BulletHoleMaterial.Object);
			//check(GEngine != nullptr);
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Decal Created"));
		}
		else
		{
			check(GEngine != nullptr);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("No Decal"));
		}

	}
	//setting up bullet's mesh
	if (!BulletMeshComponent)
	{
		BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Blueprints/Materials/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			BulletMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}
	//setting bullet's material
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Blueprints/Materials/SphereMaterial.SphereMaterial'"));
	if (Material.Succeeded())
	{
		BulletMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, BulletMeshComponent);
	}
	BulletMeshComponent->SetMaterial(0, BulletMaterialInstance);
	BulletMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	BulletMeshComponent->SetupAttachment(RootComponent);

	//deleting bullet after 3 seconds
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::FireInDirection(const FVector& ShootDirection, const FVector& playerLocationAtShooting)
{
	BulletMovementComponent->Velocity = ShootDirection * BulletMovementComponent->InitialSpeed;
	playerLocationAtShootingInBCPP = playerLocationAtShooting;
	playerLocationAtShootingInBCPP.Z = 0.0;
	//playerLocationAtShootingInBCPP.Y = 0.0;
}

int ABullet::setMultiplayer(float distance)
{
	if (distance >= 1800 && distance < 3900)
		return 1;
	else if (distance >= 3900 && distance < 7000)
		return 3;
	else if (distance >= 7000 && distance < 10000)
		return 5;
	else
		return -1;
}


//Function called when the bullet hits something
void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherActor->GetOwner() != this->GetOwner())
	{
		UGameplayStatics::SpawnDecalAttached(BulletHoleMaterialInstance, FVector(60.0f, 10.0f, 10.0f), OtherComponent, NAME_None, Hit.Location, Hit.Normal.Rotation(), EAttachLocation::KeepWorldPosition, 10);
		//check(GEngine != nullptr);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Hit.Location.ToString());
		//checking if shield was hit
		if (ATarget_Shield* TargetShield = Cast<ATarget_Shield>(OtherActor))
		{
			//getting shield size
			FVector Origin{};
			FVector BoxExtent{};
			TargetShield->GetActorBounds(false, Origin, BoxExtent);
			int points{ TargetShield->PointsForHit(Hit.Location, BoxExtent) };
			FVector HitLocation{ Hit.Location };
			HitLocation.Z = 0.0;
			//HitLocation.Y = 0;
			FVector distanceTravelledByBullet{ FVector::Dist(playerLocationAtShootingInBCPP, HitLocation) };
			//check(GEngine != nullptr);
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, distanceTravelledByBullet.ToString());
			if (ATopDownFPS1GameModeBase* GameModeBase = Cast<ATopDownFPS1GameModeBase>(GetWorld()->GetAuthGameMode()))
			{
				GameModeBase->HowMuchBulletTravelled = distanceTravelledByBullet.X;
				if (GameModeBase->canDoLimitedGame)
				{
					GameModeBase->totalPoints += points*setMultiplayer(distanceTravelledByBullet.X);
					GameModeBase->lastShot = points * setMultiplayer(distanceTravelledByBullet.X);
					GameModeBase->shotsLeft -=1 ;
				}
				else if (GameModeBase->canDoTimeGame)
				{
					GameModeBase->totalPoints += points * setMultiplayer(distanceTravelledByBullet.X);
					GameModeBase->lastShot = points * setMultiplayer(distanceTravelledByBullet.X);
					GameModeBase->shotsFired += 1;
				}
			}
			//check(GEngine != nullptr);
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, BoxExtent.ToString());
		}
		//assigning hit location for further usage
		HitLocationForShield = Hit.Location;
	}
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(BulletMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		//check(GEngine != nullptr);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hit registered"));
	}
	Destroy();
}

void ABullet::WeaponParameters(double InitialSpeed, double MaximumSpeed, const FString& WeaponType)
{
	InitSpeed = InitialSpeed;
	MaxSpeed = MaximumSpeed;
	WeaponName = WeaponType;
	BulletMovementComponent->InitialSpeed = InitialSpeed;
	BulletMovementComponent->MaxSpeed = MaximumSpeed;
}

double ABullet::BulletSpeed()
{
	return 3000.0f;
}

double ABullet::BulletGravity()
{
	return 0.0f;
}

