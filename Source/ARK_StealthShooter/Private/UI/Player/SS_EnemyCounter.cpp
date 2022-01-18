// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/SS_EnemyCounter.h"
#include "Core/SS_GameMode.h"

void USS_EnemyCounter::InitializeWidget()
{
	ASS_GameMode* CurrentGameMode = Cast<ASS_GameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(CurrentGameMode))
	{
		CurrentGameMode->OnEnemyCounterUpdateDelegate.AddDynamic(this, &USS_EnemyCounter::UpdateEnemyCounter);
	}
}

void USS_EnemyCounter::UpdateEnemyCounter(int CurrentEnemies, int MaxEnemies)
{
	EnemiesLeft = CurrentEnemies;
}
