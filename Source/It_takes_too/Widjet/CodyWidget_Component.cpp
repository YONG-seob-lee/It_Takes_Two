// Fill out your copyright notice in the Description page of Project Settings.


#include "CodyWidget_Component.h"
#include "../PlayerState/Cody_PlayerState.h"
#include "../Data/PlayerData.h"

UCodyWidget_Component::UCodyWidget_Component() {
	Level = 1;
}

void UCodyWidget_Component::InitWidget()
{
	Super::InitWidget();
	SetNewLevel(Level);
}

void UCodyWidget_Component::SetNewLevel(int32 NewLevel)
{
	/*ACody_PlayerState* PlayerState = Cast<ACody_PlayerState>();
	if (nullptr == PlayerState) return;

	CurrentStatData = PlayerState->GetPlayerData(NewLevel);
	if (CurrentStatData) {
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;
		NumOfNail = CurrentStatData->NumberOfNail;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Level %d data doesn't exist."), NewLevel);
	}*/
}
