// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "It_takes_too.h"
#include "Actor_Base_Character.h"
#include "Actor_CodyCh.generated.h"

/**
 * 
 */

UCLASS()
class IT_TAKES_TOO_API AActor_CodyCh : public AActor_Base_Character
{
	GENERATED_BODY()
public:


public:
	AActor_CodyCh();
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool GetIsThrowing();


protected:
	bool IsThrowing;

private:
	void Throw();
	void ThrowStop();
};
