// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_GameMode.h"
#include "../Character/Actor_Base_Character.h"
#include "../Character/Actor_CodyCh.h"
#include "../Controller/FirstPlayerController.h"

AITT_GameMode::AITT_GameMode()
{
<<<<<<< HEAD
	//DefaultPawnClass = AActor_Base_Character::StaticClass();
=======
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
	DefaultPawnClass = AActor_CodyCh::StaticClass();
	PlayerControllerClass = AFirstPlayerController::StaticClass();
}

void AITT_GameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));
}
