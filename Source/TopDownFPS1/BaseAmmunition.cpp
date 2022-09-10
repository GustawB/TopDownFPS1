// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAmmunition.h"

// Sets default values
ABaseAmmunition::ABaseAmmunition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("AmmunitionSceneComponent"));
	}
	if (!AmmoBoxComponent)
	{
		AmmoBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AmmunitionBoxComponent"));
		RootComponent = AmmoBoxComponent;
		AmmoBoxComponent->InitBoxExtent({ 10.0f, 10.0f, 10.0f });
	}
	if (!AmmoMeshComponent)
	{
		AmmoMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmunitionMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>AmmoMesh(TEXT("'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));
		if (AmmoMesh.Succeeded())
		{
			AmmoMeshComponent->SetStaticMesh(AmmoMesh.Object);
		}
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>AmmoMaterial(TEXT("'/Game/Blueprints/Materials/AmmoBaseMaterial.AmmoBaseMaterial'"));
	if (AmmoMaterial.Succeeded())
	{
		AmmoMaterialInstance = UMaterialInstanceDynamic::Create(AmmoMaterial.Object, AmmoMeshComponent);
	}
	AmmoMeshComponent->SetMaterial(0, AmmoMaterialInstance);
	AmmoMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseAmmunition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAmmunition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ABaseAmmunition::returnMagCap()
{
	return MagCapalicity;
}

