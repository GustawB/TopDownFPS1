// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNFPS1_API UEquipment : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipment();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
		int TotalAmmo762{};

	UPROPERTY(BlueprintReadOnly)
		int TotalAmmo556{};

	UFUNCTION(BlueprintCallable)
		int getTotalAmmo762();

	UFUNCTION(BlueprintCallable)
		int getTotalAmmo556();

	UFUNCTION()
		void substractTotalAmmo762(int newValue);

	UFUNCTION()
		void substractTotalAmmo556(int newValue);

	UFUNCTION()
		void addTotalAmmo762(int newValue);

	UFUNCTION()
		void addTotalAmmo556(int newValue);
		
};
