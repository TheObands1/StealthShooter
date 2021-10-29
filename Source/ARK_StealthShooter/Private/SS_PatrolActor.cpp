// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_PatrolActor.h"
#include "Components/SplineComponent.h"

// Sets default values
ASS_PatrolActor::ASS_PatrolActor()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));

}

FVector ASS_PatrolActor::GetWorldLocationByIndex(const int32 Index) const
{
	if (IsValid(SplineComponent) && Index <= GetLastIndex())
	{
		return SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	}
	else
	{
		return GetActorLocation();
	}
}

int32 ASS_PatrolActor::GetLastIndex() const
{
	if (IsValid(SplineComponent))
	{
		return SplineComponent->GetNumberOfSplinePoints();
	}

	return 0.0f;
}

// Called when the game starts or when spawned
void ASS_PatrolActor::BeginPlay()
{
	Super::BeginPlay();
	
}


