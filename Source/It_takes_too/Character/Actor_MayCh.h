// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor_Base_Character.h"
#include "Actor_MayCh.generated.h"

/**
 * 
 */
UCLASS()
class IT_TAKES_TOO_API AActor_MayCh : public AActor_Base_Character
{
	GENERATED_BODY()

public:
	AActor_MayCh();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Hammer;

protected:
	bool IsHaveHammer;

private:
	void Hammering();
public:
	void HammeringEnd();

};
