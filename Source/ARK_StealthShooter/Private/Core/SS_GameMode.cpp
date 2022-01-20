// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SS_EnemyCharacter.h"

ASS_GameMode::ASS_GameMode()
{
}

void ASS_GameMode::BeginPlay()
{
	TSubclassOf<AActor> ActorClass;
	TArray<AActor*> PossibleEnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASS_EnemyCharacter::StaticClass(), PossibleEnemyActors);

	//la estoy embarrando porque no estoy especificando la clase del actor

	for (AActor* PossibleEnemy : PossibleEnemyActors)
	{
		ASS_EnemyCharacter* EnemyInWorld = Cast<ASS_EnemyCharacter>(PossibleEnemy);

		if (IsValid(EnemyInWorld))
		{
			EnemiesInLevel.Add(EnemyInWorld);
		}
	}

	MaxAmountOfEnemies = EnemiesInLevel.Num();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateEnemyCounter, this, &ASS_GameMode::UpdateEnemyCounter, 0.2f, false);
}

void ASS_GameMode::ReduceEnemyCounter(ASS_EnemyCharacter* EnemyToRemove)
{
	EnemiesInLevel.Remove(EnemyToRemove);
	UpdateEnemyCounter();

	if (EnemiesInLevel.Num() == 0)
	{
		Win();
	}

}

void ASS_GameMode::UpdateEnemyCounter()
{
	OnEnemyCounterUpdateDelegate.Broadcast(EnemiesInLevel.Num(), MaxAmountOfEnemies);
}

void ASS_GameMode::GameOver()
{
	OnGameOverDelegate.Broadcast();
}

void ASS_GameMode::Win()
{
	OnWinDelegate.Broadcast();
	BP_Win();
}
