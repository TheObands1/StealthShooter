// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASS_EnemyCharacter::SetEnemyStatus(ESS_EnemyStatus NewEnemyStatus)
{
	BP_SetEnemyStatus(NewEnemyStatus);

	float NewSpeed = EnemySpeedMap[NewEnemyStatus];
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}
