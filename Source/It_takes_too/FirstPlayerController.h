// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "It_takes_too.h"
#include "GameFramework/PlayerController.h"
#include "FirstPlayerController.generated.h"

/**
 *
 */
UCLASS()
class IT_TAKES_TOO_API AFirstPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

protected:
	virtual void BeginPlay() override;
};
