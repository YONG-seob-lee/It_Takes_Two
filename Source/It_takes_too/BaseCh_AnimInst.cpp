// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCh_AnimInst.h"
#include "Actor_Base_Character.h"
#include "Actor_CodyCh.h"

UBaseCh_AnimInst::UBaseCh_AnimInst()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
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
		CheckWalk = Cody->GetPressCtrl();

		Angle = Cody->GetAngle();
		IsInAir = Cody->GetMovementComponent()->IsFalling();
		CurrentJumpCount = Cody->GetJumpCount();
		IsAimed = Cody->GetbIsAimed();
		Throwing = Cody->GetIsThrowing();
	}
}
