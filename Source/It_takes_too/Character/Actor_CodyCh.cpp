// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_CodyCh.h"
#include "../AnimInstance/Cody_AnimInst.h"

AActor_CodyCh::AActor_CodyCh()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

void AActor_CodyCh::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AActor_CodyCh::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AActor_CodyCh::Aim);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AActor_CodyCh::StopAim);
	PlayerInputComponent->BindAction(TEXT("Throw"), EInputEvent::IE_Pressed, this, &AActor_CodyCh::Throw);
	PlayerInputComponent->BindAction(TEXT("Throw"), EInputEvent::IE_Released, this, &AActor_CodyCh::ThrowStop);
}

void AActor_CodyCh::Throw()
{
	// State Part	1. can't be overlapped(action)
	if (CharState == ECharacterState::Idle || CharState == ECharacterState::Walk || CharState == ECharacterState::Jogging\
		|| CharState == ECharacterState::Sprint || CharState == ECharacterState::Jump || CharState == ECharacterState::Roll\
		|| CharState == ECharacterState::Crouch || CharState == ECharacterState::Acquire || CharState == ECharacterState::NormalRecall\
		|| CharState == ECharacterState::WalkRecall)	return;

	else	CharState = ECharacterState::ThrowStart;

	if (Cast<UCody_AnimInst>(GetMesh()->GetAnimInstance()) == nullptr) {
		UE_LOG(LogTemp, Warning, L"NULL");
	}
	Cast<UCody_AnimInst>(GetMesh()->GetAnimInstance())->ThrowAnimMontage();
}

void AActor_CodyCh::Aim()
{
	SetAimingMode(AimingMode::Aiming);

	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Sprint || CharState == ECharacterState::Roll || CharState == ECharacterState::Crouch\
		|| CharState == ECharacterState::StopJump || CharState == ECharacterState::ThrowStart || CharState == ECharacterState::ThrowEnd\
		|| CharState == ECharacterState::Acquire)	return;

	else
	{
		if (IsHoldingWalk == true)	CharState = ECharacterState::WalkAiming;
		else	CharState = ECharacterState::NormalAiming;
	}
	//////////////
	UE_LOG(LogTemp, Warning, TEXT("Aim"));

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FollowingCamera->AttachToComponent(CameraBoomAiming, FAttachmentTransformRules::KeepWorldTransform);
	UKismetSystemLibrary::MoveComponentTo(FollowingCamera, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), true, true, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);
	GetController()->SetControlRotation(CameraBoomAiming->GetRelativeRotation());
}

void AActor_CodyCh::StopAim()
{
	SetAimingMode(AimingMode::Normal);
	UE_LOG(LogTemp, Warning, TEXT("AimStop"));
	CharState = ECharacterState::Idle;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FollowingCamera->AttachToComponent(CameraBoomNormal, FAttachmentTransformRules::KeepWorldTransform);
	UKismetSystemLibrary::MoveComponentTo(FollowingCamera, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), true, true, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);

}

void AActor_CodyCh::ThrowStop()
{
	CharState = ECharacterState::Idle;
}
