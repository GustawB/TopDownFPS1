// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameActivator.h"

// Sets default values
ABaseGameActivator::ABaseGameActivator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ActivatorSceneComponent"));
	}
	if (!ActivatorBoxComponent)
	{
		ActivatorBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivatorBoxComponent"));
		RootComponent = ActivatorBoxComponent;
		ActivatorBoxComponent->InitBoxExtent({ 80.0f, 80.0f, 80.0f });
	}
	if (!ActivatorMeshComponent)
	{
		ActivatorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActivatorMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
		if (Mesh.Succeeded())
		{
			ActivatorMeshComponent->SetStaticMesh(Mesh.Object);
		}
		ActivatorMeshComponent->SetupAttachment(RootComponent);
	}
	if (!ActivatorMaterialInstance)
	{
		ActivatorMaterialInstance = CreateDefaultSubobject<UMaterialInstanceDynamic>(TEXT("ActivatorMaterialInstanceDynamic"));
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
		if (Material.Succeeded())
		{
			ActivatorMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ActivatorMeshComponent);
		}
	}
	isGameActivated = false;
	shouldEndFaster = false;
}

// Called when the game starts or when spawned
void ABaseGameActivator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseGameActivator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

