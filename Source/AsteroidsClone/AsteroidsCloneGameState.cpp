// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidsCloneGameState.h"


AAsteroidsCloneGameState::AAsteroidsCloneGameState() 
{
    Points = 0;
    PlayerLives = 2;

    AsteroidWorldSizeX = 700.0f;
    AsteroidWorldSizeY = 1150.0f;
}

int32 AAsteroidsCloneGameState::GetPoints()
{
    return Points;
}

void AAsteroidsCloneGameState::AddPoints(int32 NewPoints)
{
    Points += NewPoints;
}
