// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCh_AnimInst.h"
#include "Actor_Base_Character.h"
#include "Actor_CodyCh.h"

UBaseCh_AnimInst::UBaseCh_AnimInst()
{
	CurrentPawnSpeed = 0.0f;
}

void UBaseCh_AnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	AActor_CodyCh* Cody = Cast<AActor_CodyCh>(GetOwningActor());

	if (IsValid(Cody))
	{
		CurrentPawnSpeed = Cody->GetVelocity().Size();
		JogDirection = Cody->GetPressDirection();

		if (JogDirection != 0.0f)
		{
			JogDirection = Cody->GetPressDirection();	// Á¶±ë È®ÀÎ
		}

		State = Cody->GetState();
		Angle = Cody->GetAngle();
		CurrentJumpCount = Cody->GetJumpCount();
		Throwing = Cody->GetIsThrowing();


	}
}
