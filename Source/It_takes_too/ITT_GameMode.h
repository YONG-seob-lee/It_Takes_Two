// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "It_takes_too.h"
#include "GameFramework/GameModeBase.h"
#include "ITT_GameMode.generated.h"

/**
 *
 */
UCLASS()
class IT_TAKES_TOO_API AITT_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AITT_GameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
