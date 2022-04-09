// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_CodyCh.h"

AActor_CodyCh::AActor_CodyCh()
{
	IsThrowing = false;
}

void AActor_CodyCh::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AActor_CodyCh::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Throw"), EInputEvent::IE_Pressed, this, &AActor_CodyCh::Throw);
	PlayerInputComponent->BindAction(TEXT("Throw"), EInputEvent::IE_Released, this, &AActor_CodyCh::ThrowStop);
}

bool AActor_CodyCh::GetIsThrowing()
{
	return IsThrowing;
}

void AActor_CodyCh::Throw()
{
}

void AActor_CodyCh::ThrowStop()
{
	IsThrowing = false;
}
