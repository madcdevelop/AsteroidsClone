// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

/* 
The Ship class moves around the environment and can interact with several the asteroids by shooting them. If it is hit by an Asteroid it is destroyed.
*/
UCLASS()
class ASTEROIDSCLONE_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void EnableCollision();

	void MoveForward(float Amount);

	void RotateLeft(float Amount);

	void RotateRight(float Amount);

	void Shoot();

private:
    
    // Teleports Ship to opposite side of world when it hits end of world
    void WrapAroundWorld();

public:

protected:

    FTimerHandle CollisionSpawnTimerHandle;

    UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<class ARocket> RocketClass;

    UPROPERTY(EditAnywhere, Category = "Shooting")
    float RocketSpawnDelta;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;


private:

};
