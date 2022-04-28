// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "PlayerData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FPlayerDataTable() : Level(1), Name("Cody"), MaxHP(100.f), AttackDamage(10.f), NumberOfNail(3) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float AttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NumberOfNail;
};


UCLASS()
class IT_TAKES_TOO_API APlayerData : public AActor
{
	GENERATED_BODY()
};
