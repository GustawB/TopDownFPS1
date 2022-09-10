// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Equipment.h"
#include "KalasnikowBullet.h"
#include "KalasnikowBullet.h"
#include "Kalasnikow.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNFPS1_API AKalasnikow : public ABaseWeapon
{
	GENERATED_BODY()
	
public:

	AKalasnikow(const FObjectInitializer& ObjectInitializer);

	virtual void Fire(FVector MuzzleOffset, UEquipment* PlayerEquipment, const FVector& playerLocationAtShooting);

	virtual void Reload(UEquipment* PlayerEquipment);

	virtual void getTotalAmmo(UEquipment* PlayerEquipment);

};
