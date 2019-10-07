// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class ASTEROIDSCLONE_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

    // Called every frame
	virtual void Tick(float DeltaTime) override;

    /* Destroys Ship when Ship hits the Asteroid */
    UFUNCTION(BlueprintCallable, Category = "Collision")
    void OnShipHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void AsteroidRandomMovement();

    void SpawnShip();

private:
    
    void WrapAroundWorld();

public:	

    // Handles the delay when spawning
    FTimerHandle SpawnDelayHandle;

    FTimerHandle SpawnInvincibleHandle;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AsteroidMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UProjectileMovementComponent* AsteroidMovement;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TSubclassOf<class AShip> ShipClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    FVector MoveDirection;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    float MoveScale;

private:


};
