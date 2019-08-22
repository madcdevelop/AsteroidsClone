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

    int32 Points;
	
};