// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapons/SS_Weapon.h"
#include "SS_HealthComponent.h"

// Sets default values
ASS_BaseCharacter::ASS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	HealthComponent = CreateDefaultSubobject<USS_HealthComponent>(TEXT("HealthComponent"));

}

void ASS_BaseCharacter::StartFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartFire();
	}
}

void ASS_BaseCharacter::StopFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopFire();
	}
}

// Called when the game starts or when spawned
void ASS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(StartingWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<ASS_Weapon>(StartingWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
		}
	}
	
	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &ASS_BaseCharacter::OnHealthChanged);
		HealthComponent->OnDeathDelegate.AddDynamic(this, &ASS_BaseCharacter::OnDeath);
	}
}

void ASS_BaseCharacter::OnHealthChanged(USS_HealthComponent* MyHealthComponent, float Health, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
}

void ASS_BaseCharacter::OnDeath(USS_HealthComponent* MyHealthComponent, AController* InstigatedBy, AActor* Killer)
{
	StopFire();
	GetMovementComponent()->StopMovementImmediately();
	this->SetActorEnableCollision(false);
}



