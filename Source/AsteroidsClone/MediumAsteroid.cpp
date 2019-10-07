// Fill out your copyright notice in the Description page of Project Settings.

#include "MediumAsteroid.h"
#include "Asteroid.h"

// Sets default values
AMediumAsteroid::AMediumAsteroid()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}


// Called every frame
void AMediumAsteroid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


// Called when the game starts or when spawned
void AMediumAsteroid::BeginPlay()
{
    Super::BeginPlay();

}