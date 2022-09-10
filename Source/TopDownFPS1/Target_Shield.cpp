// Fill out your copyright notice in the Description page of Project Settings.


#include "Target_Shield.h"

// Sets default values
ATarget_Shield::ATarget_Shield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//creating ShieldBoxComponent
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Targer_ShieldSceneComponent"));
	}
	//creating mesh component and making it a RootComponent
	if (!ShieldBoxComponent)
	{
		ShieldBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ShieldBoxComponent"));
		ShieldBoxComponent->BodyInstance.SetCollisionProfileName(TEXT("Target_Shield"));
		ShieldBoxComponent->InitBoxExtent(FVector{ 50.0f, 50.0f, 50.0f });
		ShieldBoxComponent->SetSimulatePhysics(false);
		RootComponent = ShieldBoxComponent;
	}
	if (!ShieldMeshComponent)
	{
		ShieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComponent"));
		ShieldMeshComponent->SetupAttachment(RootComponent);
	}
	ShieldBoxComponent->OnComponentHit;

}

// Called when the game starts or when spawned
void ATarget_Shield::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATarget_Shield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget_Shield::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		//check(GEngine != nullptr);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Hit registered on shield"));
	}
}
//calculates point received for every hit
int ATarget_Shield::CalculatePoints(FVector ShieldEdges, FVector TotalDifference)
{
	double DifferenceX{};
	double DifferenceZ{TotalDifference.Z};
	if (ShieldEdges.X >= ShieldEdges.Y)
		DifferenceX = TotalDifference.X;
	else
		DifferenceX = TotalDifference.Y;
	float ScoreBorder{ ShieldEdges.Z / 5 };
	double distanceFromTheCenter{ sqrt((DifferenceX * DifferenceX) + (DifferenceZ * DifferenceZ)) };
	double NextPoint{ 0 };
	int points{ 10 };
	while (NextPoint <= distanceFromTheCenter)
	{
		--points;
		NextPoint += ScoreBorder;
	}
	if (points < 10)
		++points;
	return points;
	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("%lld"), points));
}
//sets up some variables to pass them to the CalculatePoints
int ATarget_Shield::PointsForHit(FVector HitLocationForShield, FVector BoxExtent)
{
	float XaxisDifference{ GetActorLocation().X - HitLocationForShield.X};
	if (XaxisDifference < 0)
		XaxisDifference *= -1;
	float YaxisDifference{ GetActorLocation().Y - HitLocationForShield.Y};
	if (YaxisDifference < 0)
		YaxisDifference *= -1;
	float ZaxisDifference{ GetActorLocation().Z - HitLocationForShield.Z};
	if (ZaxisDifference < 0)
		ZaxisDifference *= -1;
	FVector TotalDifference{ XaxisDifference, YaxisDifference, ZaxisDifference };
	FVector ShieldEdges{ BoxExtent.X/2, BoxExtent.Y / 2, BoxExtent.Z / 2 };
	return CalculatePoints(ShieldEdges, TotalDifference);
	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, ShieldEdges.ToString());
}


