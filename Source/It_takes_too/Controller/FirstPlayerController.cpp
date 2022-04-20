// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPlayerController.h"

void AFirstPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AFirstPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void AFirstPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
