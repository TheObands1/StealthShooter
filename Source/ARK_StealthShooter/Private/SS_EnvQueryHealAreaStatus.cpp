// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_EnvQueryHealAreaStatus.h"
#include "SS_HealingArea.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

USS_EnvQueryHealAreaStatus::USS_EnvQueryHealAreaStatus(const FObjectInitializer& ObjectInitializer)
{
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();
}


void USS_EnvQueryHealAreaStatus::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		ASS_HealingArea* HealingArea = Cast<ASS_HealingArea>(GetItemActor(QueryInstance, It.GetIndex()));
		float Score = 0.0f;
		if (HealingArea)
		{
			Score = HealingArea->bIsActive ? 1.0f : 0.0f;
			It.SetScore(TestPurpose, FilterType, Score, 0.0f, 1.0f);
			It.ForceItemState(HealingArea->bIsActive ? EEnvItemStatus::Passed : EEnvItemStatus::Failed);
		}
	}
}

FText USS_EnvQueryHealAreaStatus::GetDescriptionTitle() const
{
	FString DescriptionTitle = "Testing for Healing area status";
	return FText().FromString(DescriptionTitle);
}

FText USS_EnvQueryHealAreaStatus::GetDescriptionDetails() const
{
	FString Description = "Score when active: 1, Score When Inactive : 0";
	return FText().FromString(Description);
}
