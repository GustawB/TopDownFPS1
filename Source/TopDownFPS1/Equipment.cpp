// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

// Sets default values for this component's properties
UEquipment::UEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TotalAmmo556 = 25;
	TotalAmmo762 = 30;

	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Equipment"));
}


// Called when the game starts
void UEquipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UEquipment::getTotalAmmo762()
{
	return TotalAmmo762;
}

int UEquipment::getTotalAmmo556()
{
	return TotalAmmo556;
}

void UEquipment::substractTotalAmmo762(int newValue)
{
	TotalAmmo762 -= newValue;
}

void UEquipment::substractTotalAmmo556(int newValue)
{
	TotalAmmo556 -= newValue;
}

void UEquipment::addTotalAmmo762(int newValue)
{
	TotalAmmo762 += newValue;
}

void UEquipment::addTotalAmmo556(int newValue)
{
	TotalAmmo556 += newValue;
}

