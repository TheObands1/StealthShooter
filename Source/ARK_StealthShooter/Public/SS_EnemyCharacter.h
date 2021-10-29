// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SS_BaseCharacter.h"
#include "SS_EnemyCharacter.generated.h"

/**
 * 
 */

class ASS_PatrolActor;

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_EnemyCharacter : public ASS_BaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	ASS_PatrolActor* PatrolActorReference;
	
};
