// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCh_AnimInst.h"
#include "Actor_Base_Character.h"

UBaseCh_AnimInst::UBaseCh_AnimInst()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	CheckJump = false;
}


void UBaseCh_AnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	AActor_Base_Character* Cody = Cast<AActor_Base_Character>(GetOwningActor());

	if (IsValid(Cody))
	{
		CurrentPawnSpeed = Cody->GetVelocity().Size();
		JogDirection = Cody->GetPressDirection();

		if (JogDirection != 0.0f)
		{
			JogDirection = Cody->GetPressDirection();	// 조깅 확인
		}
		CheckSprint = Cody->GetPressShift();			// 스프린트 유무 확인
		CheckWalk = Cody->GetPressCtrl();

		Angle = Cody->GetAngle();
		IsInAir = Cody->GetMovementComponent()->IsFalling();

		if (Cody->GetPressSpace() == 1)		CheckJump = true;
		else	false;
	}
}
