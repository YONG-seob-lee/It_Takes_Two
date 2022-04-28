// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CharacterData.generated.h"

USTRUCT(BlueprintType)
struct FActorData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FActorData() : Level(1), MaxHP(100.f), Attack(10.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

};

UCLASS()
class IT_TAKES_TOO_API ACharacterData : public AActor
{
	GENERATED_BODY()
};
