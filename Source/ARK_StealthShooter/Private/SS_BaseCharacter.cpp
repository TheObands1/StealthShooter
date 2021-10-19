// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ASS_BaseCharacter::ASS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

}

// Called when the game starts or when spawned
void ASS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASS_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


