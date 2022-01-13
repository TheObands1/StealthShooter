// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SS_HealthBarEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API USS_HealthBarEnemy : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float HealthPercent;

public:
	UFUNCTION()
	void UpdateHealth(float Health, float MaxHealth);
	
};
