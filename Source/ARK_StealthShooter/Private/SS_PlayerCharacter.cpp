// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASS_PlayerCharacter::ASS_PlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("LookUp", this, &ASS_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookSide", this, &ASS_PlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveFoward", this, &ASS_PlayerCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASS_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASS_PlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction("EndCrouch", IE_Released, this, &ASS_PlayerCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASS_PlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASS_PlayerCharacter::StopFire);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &ASS_PlayerCharacter::StartMelee);

}

FVector ASS_PlayerCharacter::GetPawnViewLocation() const
{
	if (IsValid(CameraComponent))
	{
		return CameraComponent->GetComponentLocation();
	}
	else
	{
		return Super::GetPawnViewLocation();
	}
}

void ASS_PlayerCharacter::MoveFoward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASS_PlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASS_PlayerCharacter::StartCrouch()
{
	Crouch();
}

void ASS_PlayerCharacter::EndCrouch()
{
	UnCrouch();
}
