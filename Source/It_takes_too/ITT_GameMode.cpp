// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_GameMode.h"
#include "Actor_Base_Character.h"
#include "FirstPlayerController.h"

AITT_GameMode::AITT_GameMode()
{
	DefaultPawnClass = AActor_Base_Character::StaticClass();
	PlayerControllerClass = AFirstPlayerController::StaticClass();
}

void AITT_GameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
}
