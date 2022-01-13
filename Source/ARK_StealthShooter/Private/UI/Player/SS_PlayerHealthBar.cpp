// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/SS_PlayerHealthBar.h"
#include "SS_BaseCharacter.h"
#include "SS_PlayerCharacter.h"
#include "SS_HealthComponent.h"
#include "Kismet/GameplayStatics.h"

void USS_PlayerHealthBar::InitializeWidget()
{
	APawn* PossiblePawn = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (IsValid(PossiblePawn))
	{
		ASS_BaseCharacter* PossibleBaseCharacter = Cast<ASS_BaseCharacter>(PossiblePawn);
		if (IsValid(PossibleBaseCharacter))
		{
			ASS_PlayerCharacter* PossiblePlayer = Cast<ASS_PlayerCharacter>(PossibleBaseCharacter);
			if (IsValid(PossiblePlayer))
			{
				USS_HealthComponent* PlayerHealthComponent = PossiblePlayer->GetHealthComponent();

				if (IsValid(PlayerHealthComponent))
				{
					PlayerHealthComponent->OnHealthUpdateDelegate.AddDynamic(this, &USS_PlayerHealthBar::UpdateHealthBar);
				}
			}
		}
	}
}

void USS_PlayerHealthBar::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	HealthPercentage = CurrentHealth / MaxHealth;

	HealthColor = FMath::Lerp(EmptyHealthColor, FullHealthColor, HealthPercentage);
}
