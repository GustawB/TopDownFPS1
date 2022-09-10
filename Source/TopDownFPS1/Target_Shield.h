// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Target_Shield.generated.h"

UCLASS()
class TOPDOWNFPS1_API ATarget_Shield : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATarget_Shield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Target's UBoxComponent
	UPROPERTY(VisibleDefaultsOnly, Category = Shield)
		UBoxComponent* ShieldBoxComponent;

	//Target's mesh
	UPROPERTY(EditAnywhere, Category = Shield_Mesh)
		UStaticMeshComponent* ShieldMeshComponent;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


	//Prototype for a function that is returning points per hit
	UFUNCTION()
		int PointsForHit(FVector HitLocationForShield, FVector BoxExtent);

	//Function returning point for a hit
	UFUNCTION()
		int CalculatePoints(FVector ShieldEdges, FVector TotalDifference);
};