// Copyright Epic Games, Inc. All Rights Reserved.


#include "TopDownFPS1GameModeBase.h"

void ATopDownFPS1GameModeBase::StartPlay()
{
	Super::StartPlay();
	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Everything's alright"));
	
	// these are modified in Bullet.cpp
	totalPoints = 0;
	lastShot = 0;
	shotsLeft = 10;
	shotsFired = 0;
	canDoLimitedGame = false;
	canDoTimeGame = false;
	secondsLeft = 30;
	HowMuchBulletTravelled = 0;
}

void ATopDownFPS1GameModeBase::setMaxDistanceTravelledByBullet()
{
	if (HowMuchBulletTravelled > MaxHowMuchBulletTravelled)
		MaxHowMuchBulletTravelled = HowMuchBulletTravelled;
}

void ATopDownFPS1GameModeBase::decrementSeconds()
{
	--secondsLeft;
}

void ATopDownFPS1GameModeBase::startTimer()
{
	GetWorldTimerManager().SetTimer(GameTimer, this, &ATopDownFPS1GameModeBase::decrementSeconds, 1, true);
}

void ATopDownFPS1GameModeBase::resetTimer()
{
	GetWorldTimerManager().ClearTimer(GameTimer);
}

