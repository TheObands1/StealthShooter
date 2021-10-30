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

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_EnemyCharacter : public ASS_BaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	ASS_PatrolActor* PatrolActorReference;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TMap<ESS_EnemyStatus, float> EnemySpeedMap;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_SetEnemyStatus(ESS_EnemyStatus NewEnemyStatus);

protected:
	UFUNCTION(BlueprintCallable)
	void SetEnemyStatus(ESS_EnemyStatus NewEnemyStatus);
	
};
