// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SS_Weapon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASS_Weapon::ASS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

}

// Called when the game starts or when spawned
void ASS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

