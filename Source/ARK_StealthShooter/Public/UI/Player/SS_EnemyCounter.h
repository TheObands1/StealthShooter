// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SS_EnemyCounter.generated.h"

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API USS_EnemyCounter : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	int EnemiesLeft;

protected:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void UpdateEnemyCounter(int CurrentEnemies, int MaxEnemies);
	
};
