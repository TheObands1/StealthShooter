// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SS_BaseCharacter.h"
#include "SS_EnemyCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ESS_EnemyStatus : uint8
{
	EnemyStatus_Patrol = 0				UMETA(DisplayName = "Patrol"),
	EnemyStatus_Investigating = 1		UMETA(DisplayName = "Investigating"),
	EnemyStatus_Combat = 2				UMETA(DisplayName = "Combat")
};


class ASS_PatrolActor;
class UWidgetComponent;
class USS_HealthBarEnemy;
class USS_HealthComponent;
class ASS_AIController;

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_EnemyCharacter : public ASS_BaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* WidgetHealthBarComponent;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	bool bIsShowingHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = 0.0f))
	float TimeToDelayHidingOfHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	ASS_PatrolActor* PatrolActorReference;

	USS_HealthBarEnemy* EnemyHealthBarReference;
	
	FTimerHandle TimerHandle_HideHealthBar;

	ASS_AIController* MyAIControllerReference;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TMap<ESS_EnemyStatus, float> EnemySpeedMap;

public:
	ASS_EnemyCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SetEnemyStatus(ESS_EnemyStatus NewEnemyStatus);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HideHealthBar();

	void ShowHealthBar();

	UFUNCTION(BlueprintCallable)
	void SetEnemyStatus(ESS_EnemyStatus NewEnemyStatus);

	virtual void OnHealthChanged(USS_HealthComponent* MyHealthComponent, float Health, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;

	virtual void OnDeath(USS_HealthComponent* MyHealthComponent, class AController* InstigatedBy, AActor* Killer) override;
};
