// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "SmallAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDSCLONE_API ASmallAsteroid : public AAsteroid
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    ASmallAsteroid();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

};
