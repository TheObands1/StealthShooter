// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SS_BaseCharacter.generated.h"

class ASS_Weapon;

UCLASS()
class ARK_STEALTHSHOOTER_API ASS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ASS_Weapon> StartingWeaponClass;

	UPROPERTY(BlueprintReadOnly)
	ASS_Weapon* CurrentWeapon;



public:
	// Sets default values for this character's properties
	ASS_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
