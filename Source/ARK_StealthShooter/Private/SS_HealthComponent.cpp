// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_HealthComponent.h"
#include "GameFramework/Actor.h"
#include "..\Public\SS_HealthComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
USS_HealthComponent::USS_HealthComponent()
{
	DefaultHealth = 200.0f;
}

// Called when the game starts
void USS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = DefaultHealth;
	
	AActor* ActorOwner = GetOwner();
	if (IsValid(ActorOwner))
	{
		ActorOwner->OnTakeAnyDamage.AddDynamic(this, &USS_HealthComponent::TakeAnyDamage);
	}
	
}

void USS_HealthComponent::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0 || bIsDead)
	{
		return;
	}

	if (IsValid(DamagedActor))
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);

		if (CurrentHealth > 0)
		{
			OnHealthChangedDelegate.Broadcast(this, CurrentHealth, Damage, DamageType, InstigatedBy, DamageCauser);
		}
		else
		{
			bIsDead = true;
			OnDeathDelegate.Broadcast(this, InstigatedBy, DamageCauser);
		}
	}
}



