// Fill out your copyright notice in the Description page of Project Settings.

#include "SmallAsteroid.h"
#include "Asteroid.h"


// Sets default values
ASmallAsteroid::ASmallAsteroid()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmallAsteroid::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ASmallAsteroid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}