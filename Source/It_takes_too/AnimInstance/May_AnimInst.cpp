// Fill out your copyright notice in the Description page of Project Settings.


#include "May_AnimInst.h"
#include "../Character/Actor_MayCh.h"

void UMayCh_AnimInst::AnimNotify_HammeringEndCheck()
{
	UE_LOG(LogTemp, Warning, L"EndCheck");
	AActor_MayCh* May = Cast<AActor_MayCh>(GetOwningActor());

	May->HammeringEnd();
} 