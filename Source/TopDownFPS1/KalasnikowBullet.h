// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "KalasnikowBullet.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNFPS1_API AKalasnikowBullet : public ABullet
{
	GENERATED_BODY()

public:

	AKalasnikowBullet(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY()
		double Speed{9000.0f};

	UPROPERTY()
		double Gravity{ 0.3f };
};
