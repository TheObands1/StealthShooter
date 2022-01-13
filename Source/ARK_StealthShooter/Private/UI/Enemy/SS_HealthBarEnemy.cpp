// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enemy/SS_HealthBarEnemy.h"

void USS_HealthBarEnemy::UpdateHealth(float Health, float MaxHealth)
{
	HealthPercent = Health / MaxHealth;
}
