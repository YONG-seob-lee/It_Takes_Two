// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
#include "Engine/GameInstance.h"
#include "ITT_Instance.generated.h"

/**
 * 
 */
struct FActorData;
class UDataTable;


UCLASS()
class IT_TAKES_TOO_API UITT_Instance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UITT_Instance();
	FActorData* GetActorData(int32 Level);

private:
	UPROPERTY()
	UDataTable* Actor_DT;
};
