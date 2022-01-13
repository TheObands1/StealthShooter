// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SS_PlayerHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API USS_PlayerHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	float HealthPercentage;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FLinearColor HealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor FullHealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor EmptyHealthColor;

protected:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

};
