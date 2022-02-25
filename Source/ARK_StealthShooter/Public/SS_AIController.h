// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API ASS_AIController : public AAIController
{
	GENERATED_BODY()

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:
	ASS_AIController(const FObjectInitializer& ObjectInitializer);
	
};
