// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
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
<<<<<<< HEAD
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
=======

>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
	void ThrowStop();

protected:

private:
	void Throw();

	void Aim();
	void StopAim();

<<<<<<< HEAD
public:
	void PostInit();
	APlayerController* Cody;
=======
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
};
