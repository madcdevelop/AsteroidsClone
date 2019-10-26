// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AsteroidsCloneGameState.generated.h"

/*
Holds information about the Player and how many points they have currently. 
 */
UCLASS()
class ASTEROIDSCLONE_API AAsteroidsCloneGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

    AAsteroidsCloneGameState();

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    int32 GetPoints();

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void AddPoints(int32 NewPoints);

protected:

private:


public:

    UPROPERTY(BlueprintReadWrite, Category = "Game")
    float AsteroidWorldSizeX;

    UPROPERTY(BlueprintReadWrite, Category = "Game")
    float AsteroidWorldSizeY;

    /* Current amount of points player has */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Game")
    int32 Points;

    /* Current amount of lives player has */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Game")
    int32 PlayerLives;

    /* Level name to load */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Game")
    FName LevelName;
	
protected:


private:
    


};
