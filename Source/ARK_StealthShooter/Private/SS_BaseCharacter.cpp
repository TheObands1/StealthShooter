// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Weapons/SS_Weapon.h"
#include "SS_HealthComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Core/SS_GameMode.h"
#include "Components/PawnNoiseEmitterComponent.h"
// Sets default values
ASS_BaseCharacter::ASS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	HealthComponent = CreateDefaultSubobject<USS_HealthComponent>(TEXT("HealthComponent"));

	CharacterNoiseEmmiter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("CharacterNoiseEmmiter"));

	CharacterNoiseEmmiter->SetAutoActivate(true);
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

	MyAnimInstance = GetMesh()->GetAnimInstance();

	if (IsValid(MyAnimInstance))
	{
		MyAnimInstance->OnMontageEnded.AddDynamic(this, &ASS_BaseCharacter::StopMelee);
	}

	GameModeReference = Cast<ASS_GameMode>(GetWorld()->GetAuthGameMode());
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

void ASS_BaseCharacter::StartMelee()
{
	if (bIsDoingMeleeAttack)
	{
		return;
	}

	if (IsValid(MyAnimInstance) && IsValid(MeleeAttackMontage))
	{
		GetMovementComponent()->StopMovementImmediately();
		MyAnimInstance->Montage_Play(MeleeAttackMontage);
		bIsDoingMeleeAttack = true;
	}
}

void ASS_BaseCharacter::StopMelee(UAnimMontage* AnimMontageReference, bool bIsInterrumpted)
{
	if (AnimMontageReference == MeleeAttackMontage)
	{
		bIsDoingMeleeAttack = false;
	}
}

void ASS_BaseCharacter::DoMeleeAttack()
{
	const FVector MeleeAttackLocation = GetMesh()->GetSocketLocation(MeleeSocketName);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	TArray<AActor*> DamagedActors;

	bool bHasAnActorBeenHit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), MeleeAttackLocation, MeleeAttackRange, MeleeObjectTypes, AActor::StaticClass(), ActorsToIgnore, DamagedActors);
	
	if (bHasAnActorBeenHit)
	{
		AActor* HitActor = DamagedActors[0];
		if (IsValid(HitActor))
		{
			USS_HealthComponent* HitActorHealthComponent = Cast<USS_HealthComponent>(HitActor->GetComponentByClass(USS_HealthComponent::StaticClass()));

			if (IsValid(HitActorHealthComponent))
			{
				HitActorHealthComponent->KillAutomatically(GetController(), this);
			}
		}
	}
}

void ASS_BaseCharacter::CharacterMakeNoise(const float Loudness, const FVector NoiseLocation)
{
	if (IsValid(CharacterNoiseEmmiter))
	{
		CharacterNoiseEmmiter->MakeNoise(this, Loudness, NoiseLocation);
	}
}



