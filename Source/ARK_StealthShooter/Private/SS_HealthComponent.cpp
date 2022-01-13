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
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandler_UpdateInitialHealth, this, &USS_HealthComponent::UpdateHealth, 0.2f, false);
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
		UpdateHealth();
	}
}

void USS_HealthComponent::KillAutomatically(AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsDead)
	{
		return;
	}

	CurrentHealth = 0.0f;
	bIsDead = true;
	UpdateHealth();
	OnDeathDelegate.Broadcast(this, InstigatedBy, DamageCauser);
}

void USS_HealthComponent::Heal(const float HealthAmount)
{
	if (bIsDead)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + HealthAmount, 0.0f, DefaultHealth);
	OnHealthUpdateDelegate.Broadcast(CurrentHealth, DefaultHealth);


}

void USS_HealthComponent::UpdateHealth()
{
	OnHealthUpdateDelegate.Broadcast(CurrentHealth, DefaultHealth);
}

bool USS_HealthComponent::IsFriendly(const AActor* ActorA, const AActor* ActorB)
{
	if (ActorA == nullptr || ActorB == nullptr)
	{
		return true;
	}

	USS_HealthComponent* HealthComponentA = ActorA->FindComponentByClass<USS_HealthComponent>();
	USS_HealthComponent* HealthComponentB = ActorB->FindComponentByClass<USS_HealthComponent>();

	if (HealthComponentA == nullptr || HealthComponentB == nullptr)
	{
		return true;
	}

	return HealthComponentA->TeamNumber == HealthComponentB->TeamNumber;
}



