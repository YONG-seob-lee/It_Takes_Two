// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCh_AnimInst.h"
#include "MayCh_AnimInst.generated.h"

/**
 * 
 */
UCLASS()
class IT_TAKES_TOO_API UMayCh_AnimInst : public UBaseCh_AnimInst
{
	GENERATED_BODY()
	
private:

	UFUNCTION()
	void AnimNotify_HammeringEndCheck();
};
