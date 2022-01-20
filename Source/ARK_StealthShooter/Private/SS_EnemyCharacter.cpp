// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "SS_HealthComponent.h"
#include "UI/Enemy/SS_HealthBarEnemy.h"
#include "Core/SS_GameMode.h"
#include "SS_AIController.h"

ASS_EnemyCharacter::ASS_EnemyCharacter()
{
	WidgetHealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetHealthBarComponent"));
	WidgetHealthBarComponent->SetupAttachment(RootComponent);
	WidgetHealthBarComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TimeToDelayHidingOfHealthBar = 1.0f;
}

void ASS_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(WidgetHealthBarComponent->GetUserWidgetObject()))
	{
		EnemyHealthBarReference = Cast<USS_HealthBarEnemy>(WidgetHealthBarComponent->GetUserWidgetObject());
		if (IsValid(EnemyHealthBarReference))
		{
			GetHealthComponent()->OnHealthUpdateDelegate.AddDynamic(EnemyHealthBarReference, &USS_HealthBarEnemy::UpdateHealth);
			HideHealthBar();
		}
	}

	MyAIControllerReference = Cast<ASS_AIController>(GetController());
}

void ASS_EnemyCharacter::HideHealthBar()
{

	bIsShowingHealthBar = false;
	EnemyHealthBarReference->SetVisibility(ESlateVisibility::Hidden);
}

void ASS_EnemyCharacter::ShowHealthBar()
{
	bIsShowingHealthBar = true;
	EnemyHealthBarReference->SetVisibility(ESlateVisibility::Visible);
}


void ASS_EnemyCharacter::SetEnemyStatus(ESS_EnemyStatus NewEnemyStatus)
{
	BP_SetEnemyStatus(NewEnemyStatus);

	float NewSpeed = EnemySpeedMap[NewEnemyStatus];
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;

}

void ASS_EnemyCharacter::OnHealthChanged(USS_HealthComponent* MyHealthComponent, float Health, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnHealthChanged(MyHealthComponent, Health, Damage, DamageType, InstigatedBy, DamageCauser);

	if (MyHealthComponent->bIsActorDead())
	{
		if (IsValid(EnemyHealthBarReference))
		{
			HideHealthBar();
		}
	}
	else
	{
		if (IsValid(EnemyHealthBarReference))
		{
			if (bIsShowingHealthBar)
			{
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideHealthBar);
			}
			else
			{
				ShowHealthBar();
			}

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideHealthBar, this, &ASS_EnemyCharacter::HideHealthBar, TimeToDelayHidingOfHealthBar, false);
		}

	}
}

void ASS_EnemyCharacter::OnDeath(USS_HealthComponent* MyHealthComponent, AController* InstigatedBy, AActor* Killer)
{
	Super::OnDeath(MyHealthComponent, InstigatedBy, Killer);
	if (GameModeReference)
	{
		GameModeReference->ReduceEnemyCounter(this);
	}

	/*
	if (IsValid(MyAIControllerReference))
	{
		MyAIControllerReference->DeactivateAIPerception();
		MyAIControllerReference->UnPossess();
		MyAIControllerReference->Destroy();
	}
	*/
}
