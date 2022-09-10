// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "TPHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNFPS1_API ATPHUD : public AHUD
{
	GENERATED_BODY()

protected:
	//Crosshair drawn at the center of the screen
	//UPROPERTY(EditDefaultsOnly)
	//	UTexture2D* CrosshairTexture;

public:
	//fuction that draws a crosshair on the screen
	//virtual void DrawHUD() override;
	
};
