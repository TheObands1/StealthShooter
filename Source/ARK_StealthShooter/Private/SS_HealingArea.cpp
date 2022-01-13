// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_HealingArea.h"
#include "Components/StaticMeshComponent.h"
#include "SS_BaseCharacter.h"
#include "SS_HealthComponent.h"

// Sets default values
ASS_HealingArea::ASS_HealingArea()
{
	AreaMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealingAreaMeshComponent"));
	SetRootComponent(AreaMeshComponent);

	bIsActive = true;
}

// Called when the game starts or when spawned
void ASS_HealingArea::BeginPlay()
{
	Super::BeginPlay();

	if (AreaMeshComponent)
	{
		AreaMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASS_HealingArea::OnAreaMeshOverlap);
	}
	
}

void ASS_HealingArea::OnAreaMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		ASS_BaseCharacter* PossibleCharacter = Cast<ASS_BaseCharacter>(OtherActor);

		if (IsValid(PossibleCharacter))
		{
			Heal(PossibleCharacter);
		}
	}
}

void ASS_HealingArea::Heal(ASS_BaseCharacter* CharacterToHeal)
{
	USS_HealthComponent* CharacterHealthComponent = CharacterToHeal->GetHealthComponent();

	if (CharacterHealthComponent)
	{
		CharacterHealthComponent->Heal(HealingAmount);
	}

	bIsActive = false;
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AreaMeshComponent->SetVisibility(false);
	GetWorldTimerManager().SetTimer(TimerHandle_Cooldown, this, &ASS_HealingArea::ResetHealingArea, CooldownTime);
}

void ASS_HealingArea::ResetHealingArea()
{
	bIsActive = true;
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AreaMeshComponent->SetVisibility(true);
}

