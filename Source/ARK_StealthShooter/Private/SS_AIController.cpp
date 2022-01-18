// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_AIController.h"
#include "SS_HealthComponent.h"

ETeamAttitude::Type ASS_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const AActor* OtherActor = &Other;
    return (USS_HealthComponent::IsFriendly(GetPawn(), OtherActor)) ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

ASS_AIController::ASS_AIController()
{
    SetGenericTeamId(FGenericTeamId(1));
}
