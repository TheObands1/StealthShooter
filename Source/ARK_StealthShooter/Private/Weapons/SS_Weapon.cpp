// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SS_Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "../ARK_StealthShooter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASS_Weapon::ASS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	ShotDistance = 10000.0f;
	ShotDamage = 20.0f;

	bIsDebugging = false;
	RoundsPerMinute = 300;

}

// Called when the game starts or when spawned
void ASS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60 / RoundsPerMinute;
}

// Called every frame
void ASS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASS_Weapon::StartFire()
{
	float TimeToCalculate = LastFireTime + TimeBetweenShots;
	float CurrentSeconds = GetWorld()->TimeSeconds;
	float MaxValueOfDelay = TimeToCalculate - CurrentSeconds;
	float FirstDelay = FMath::Max(0.0f, MaxValueOfDelay);
	GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &ASS_Weapon::Fire, TimeBetweenShots, true, FirstDelay);
}

void ASS_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
}

void ASS_Weapon::Fire()
{
	AActor* MyOwner = GetOwner();

	if (IsValid(MyOwner))
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * ShotDistance);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;

		bool bDidLineTraceHit = GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_GameTraceChannel1, QueryParams);

		if (bDidLineTraceHit)
		{
			AActor* HitActor = Hit.GetActor();

			UGameplayStatics::ApplyPointDamage(HitActor, ShotDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), MyOwner, DamageType);

			if (bIsDebugging)
			{
				DrawDebugLine(GetWorld(), EyeLocation, Hit.ImpactPoint, FColor::White, false, 1.0f, 0.0f, 1.0f);
			}
		}

	}
	LastFireTime = GetWorld()->TimeSeconds;
}

