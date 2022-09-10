// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseAmmunition.generated.h"

UCLASS()
class TOPDOWNFPS1_API ABaseAmmunition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAmmunition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		FString AmmoType;

	UPROPERTY(VisibleDefaultsOnly)
		int MagCapalicity;

	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent* AmmoBoxComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* AmmoMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UMaterialInstanceDynamic* AmmoMaterialInstance;

	UFUNCTION()
		int returnMagCap();

};
