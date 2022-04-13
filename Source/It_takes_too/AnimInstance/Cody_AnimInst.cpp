// Fill out your copyright notice in the Description page of Project Settings.


#include "Cody_AnimInst.h"
#include "../Character/Actor_Base_Character.h"
#include "../Character/Actor_CodyCh.h"

UCody_AnimInst::UCody_AnimInst()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ThrowAnimMontageFinder(TEXT("/Game/BaseCharacter/Animation/Montage/Throw_Nail_Montage.Throw_Nail_Montage"));
	if (ThrowAnimMontageFinder.Succeeded() == false)
		return;

	ThrowAnimMontageInstance = ThrowAnimMontageFinder.Object;
}

void UCody_AnimInst::AnimNotify_ThrowStopCheck()
{
	UE_LOG(LogTemp, Warning, L"AnimNotify_ThrowStopCheck");
	AActor_CodyCh* Cody = Cast<AActor_CodyCh>(GetOwningActor());

	Cody->ThrowStop();
}

void UCody_AnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCody_AnimInst::ThrowAnimMontage()
{
	Montage_Play(ThrowAnimMontageInstance);
}
