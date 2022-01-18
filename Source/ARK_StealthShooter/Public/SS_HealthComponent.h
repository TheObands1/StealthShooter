// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SS_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, USS_HealthComponent*, HealthComponent, float, Health, float, Damage, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeathSignature, USS_HealthComponent*, HealthComponent, class AController*, InstigatedBy, AActor*, Killer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdateSignature, float, CurrentHealth, float, MaxHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARK_STEALTHSHOOTER_API USS_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected: 

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (ClampMin = 0.1f))
	float DefaultHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	uint8 TeamNumber;

	FTimerHandle TimerHandler_UpdateInitialHealth;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeathDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdateSignature OnHealthUpdateDelegate;


public:	
	// Sets default values for this component's properties
	USS_HealthComponent();

	UFUNCTION(BlueprintCallable)
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void KillAutomatically(AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void Heal(const float HealthAmount);

	UFUNCTION()
	void UpdateHealth();

	bool bIsActorDead() { return bIsDead; };

	static bool IsFriendly(const AActor* ActorA, const AActor* ActorB);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
