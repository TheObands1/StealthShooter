// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_Weapon.generated.h"

class UStaticMeshComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_Weapon : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	bool bIsDebugging;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* WeaponMesh;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 0.1f))
	float ShotDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 0.0f))
	float ShotDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 0.1f))
	float RoundsPerMinute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = 0.1f))
	float TimeBetweenShots;

	float LastFireTime;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	FTimerHandle TimerHandle_AutoFire;
public:	
	// Sets default values for this actor's properties
	ASS_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartFire();

	void StopFire();

	void Fire();

};
