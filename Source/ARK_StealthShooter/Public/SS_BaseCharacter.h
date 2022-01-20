// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SS_BaseCharacter.generated.h"

class ASS_Weapon;
class USS_HealthComponent;
class UAnimMontage;
class ASS_GameMode;
class UPawnNoiseEmitterComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USS_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPawnNoiseEmitterComponent* CharacterNoiseEmmiter;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsDoingMeleeAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeAttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	UAnimMontage* MeleeAttackMontage;

	UAnimInstance* MyAnimInstance;

	ASS_GameMode* GameModeReference;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TArray<TEnumAsByte<EObjectTypeQuery>> MeleeObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ASS_Weapon> StartingWeaponClass;

	UPROPERTY(BlueprintReadOnly)
	ASS_Weapon* CurrentWeapon;

public:
	// Sets default values for this character's properties
	ASS_BaseCharacter();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION()
	USS_HealthComponent* GetHealthComponent() { return HealthComponent; };

	UFUNCTION()
	void CharacterMakeNoise(const float Loudness, const FVector NoiseLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHealthChanged(USS_HealthComponent* MyHealthComponent, float Health, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	virtual void OnDeath(USS_HealthComponent* MyHealthComponent, class AController* InstigatedBy, AActor* Killer);

	UFUNCTION(BlueprintCallable)
	void StartMelee();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_StartMelee();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_StopMelee();

	UFUNCTION(BlueprintCallable)
	void StopMelee(UAnimMontage* AnimMontageReference, bool bIsInterrumpted);

	UFUNCTION(BlueprintCallable)
	void DoMeleeAttack();


};
