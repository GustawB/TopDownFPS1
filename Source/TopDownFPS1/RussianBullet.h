// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "RussianBullet.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNFPS1_API ARussianBullet : public ABullet
{
	GENERATED_BODY()

public:

	ARussianBullet(const FObjectInitializer& ObjectInitializer);

	virtual double BulletSpeed();

	virtual double BulletGravity();

	UPROPERTY()
		double Speed{ 12000.0f };

	UPROPERTY()
		double Gravity{ 0.3f };
};
