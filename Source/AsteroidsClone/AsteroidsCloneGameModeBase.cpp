// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidsCloneGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AAsteroidsCloneGameModeBase::AAsteroidsCloneGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP_Ship"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

