// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
#include "BaseCh_AnimInst.h"
#include "Cody_AnimInst.generated.h"

/**
 * 
 */
UCLASS()
class IT_TAKES_TOO_API UCody_AnimInst : public UBaseCh_AnimInst
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void AnimNotify_ThrowStopCheck();

public:
	UCody_AnimInst();
	virtual void NativeUpdateAnimation(float DeltaSeconds)	override;

	UFUNCTION()
	void ThrowAnimMontage();

private:
	UAnimMontage* ThrowAnimMontageInstance = nullptr;
};
