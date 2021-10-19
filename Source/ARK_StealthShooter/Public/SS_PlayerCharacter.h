// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SS_BaseCharacter.h"
#include "SS_PlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class ARK_STEALTHSHOOTER_API ASS_PlayerCharacter : public ASS_BaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

public:
	
	ASS_PlayerCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveFoward(float AxisValue);

	void MoveRight(float AxisValue);

	void StartCrouch();

	void EndCrouch();
};
