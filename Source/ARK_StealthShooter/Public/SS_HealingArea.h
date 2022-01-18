// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_HealingArea.generated.h"

class UStaticMeshComponent;
class ASS_BaseCharacter;

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_HealingArea : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AreaMeshComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float HealingAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float CooldownTime;
	
	FTimerHandle TimerHandle_Cooldown;

public:
	UPROPERTY(BlueprintReadWrite)
	uint8 bIsActive;
	
public:	
	// Sets default values for this actor's properties
	ASS_HealingArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAreaMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Heal(ASS_BaseCharacter* CharacterToHeal);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Heal();

	UFUNCTION()
	void ResetHealingArea();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ResetHealingArea();

};
