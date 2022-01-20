// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SS_GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyCounterUpdateSignature, int, CurrentAmountOfEnemies, int, MaxAmountOfEnemies);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOverSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWinSignature);
/**
 * 
 */

class ASS_EnemyCharacter;

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Enemies")
	int MaxAmountOfEnemies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemies")
	TArray<ASS_EnemyCharacter*> EnemiesInLevel;

	FTimerHandle TimerHandle_UpdateEnemyCounter;

public:
	ASS_GameMode();

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnemyCounterUpdateSignature OnEnemyCounterUpdateDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameOverSignature OnGameOverDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnWinSignature OnWinDelegate;

protected:

	virtual void BeginPlay() override;

	void UpdateEnemyCounter();

	void GameOver();

	void Win();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GameOver();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Win();

public: 
	void ReduceEnemyCounter(ASS_EnemyCharacter* EnemyToRemove);
	
};
