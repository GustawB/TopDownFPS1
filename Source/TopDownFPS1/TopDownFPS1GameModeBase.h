// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "TopDownFPS1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNFPS1_API ATopDownFPS1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void StartPlay() override;


public:
	//ATPCharacter is a player character
	UPROPERTY()
		TSubclassOf<class ATPCharacter> CharacterClass;

	UPROPERTY(BlueprintReadWrite)
		float totalPoints;

	UPROPERTY(BlueprintReadWrite)
		float lastShot;

	UPROPERTY(BlueprintReadWrite)
		float shotsLeft;

	UPROPERTY(BlueprintReadWrite)
		float shotsFired;

	UPROPERTY(BlueprintReadWrite)
		bool canDoLimitedGame;

	UPROPERTY(BlueprintReadWrite)
		bool canDoTimeGame;

	UPROPERTY(BlueprintReadWrite)
		float HowMuchBulletTravelled;

	UPROPERTY(BlueprintReadWrite)
		float MaxHowMuchBulletTravelled;

	UPROPERTY()
		FTimerHandle GameTimer;

	UPROPERTY(BlueprintReadWrite)
		int secondsLeft{};

	UFUNCTION(BlueprintCallable)
		void setMaxDistanceTravelledByBullet();

	UFUNCTION(BlueprintCallable)
		void decrementSeconds();

	UFUNCTION(BlueprintCallable)
		void startTimer();

	UFUNCTION(BlueprintCallable)
		void resetTimer();
};
