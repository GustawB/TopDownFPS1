// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Equipment.h"
#include "RussianBullet.h"
#include "RussianGun.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNFPS1_API ARussianGun : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ARussianGun(const FObjectInitializer& ObjectInitializer);

	virtual void Fire(FVector MuzzleOffset, UEquipment* PlayerEquipment, const FVector& playerLocationAtShooting);

	virtual void Reload(UEquipment* PlayerEquipment);

	virtual void getTotalAmmo(UEquipment* PlayerEquipment);

};
