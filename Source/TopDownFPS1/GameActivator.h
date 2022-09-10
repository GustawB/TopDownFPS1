// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameActivator.generated.h"

UCLASS()
class TOPDOWNFPS1_API AGameActivator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameActivator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
		bool isAnyGameActivated;

	UPROPERTY(BlueprintReadWrite)
		bool isTimeGameActivated;

	UPROPERTY(BlueprintReadWrite)
		bool isLimitedGameActivated;


	UPROPERTY(VisibleDefaultsOnly)
		UBoxComponent* ActivatorBoxComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* ActivatorMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UMaterialInstanceDynamic* ActivatorMaterialInstance;

};
