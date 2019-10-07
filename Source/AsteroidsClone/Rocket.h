// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Classes/GameFramework/ProjectileMovementComponent.h"

#include "Rocket.generated.h"


/* 
The Rocket can be fired by the Ship class. 
The Rocket explodes and destroys an object once it hits it.
*/
UCLASS()
class ASTEROIDSCLONE_API ARocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocket();

    // Called every frame
	virtual void Tick(float DeltaTime) override;

    /** Destroys asteroid and Rocket upon the Rocket hitting the Asteroid. */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void OnRocketHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    
    bool WrapAroundWorld();

public:	
    
    FVector RocketOriginalLocation;

    float RocketDistance;

    UPROPERTY(EditAnywhere, Category = "Projectile")
    float RocketMaxDistance;
   
protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RocketMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* RocketMovement;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TSubclassOf<class AMediumAsteroid> MediumAsteroidClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TSubclassOf<class ASmallAsteroid> SmallAsteroidClass;

};
