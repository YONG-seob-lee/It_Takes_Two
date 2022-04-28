// Fill out your copyright notice in the Description page of Project Settings.


#include "ITT_Instance.h"
#include "../Data/CharacterData.h"

UITT_Instance::UITT_Instance() {
	FString CharacterDataPath = TEXT("/Game/Data/CharacterData.CharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ACTOR(*CharacterDataPath);
	if (DT_ACTOR.Succeeded()) {
		Actor_DT = DT_ACTOR.Object;
	}
}

FActorData* UITT_Instance::GetActorData(int32 Level)
{
	return Actor_DT->FindRow<FActorData>(*FString::FromInt(Level), TEXT(""));
}
