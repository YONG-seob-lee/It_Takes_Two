// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
#include "Animation/AnimInstance.h"
#include "../Character/Actor_Base_Character.h"
#include "BaseCh_AnimInst.generated.h"

/**
 *
 */
UCLASS()
class IT_TAKES_TOO_API UBaseCh_AnimInst : public UAnimInstance
{
	GENERATED_BODY()

private:

	UFUNCTION()
	void AnimNotify_RollEndCheck();
public:
	UBaseCh_AnimInst();
	virtual void NativeUpdateAnimation(float DeltaSeconds)	 override;

	UFUNCTION()
		void RollAnimMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float JogDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	int32 CurrentJumpCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float SinAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDoubleJumped;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnumClass, Meta = (AllowPrivateAccess = true))
	ECharacterState State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnumClass, Meta = (AllowPrivateAccess = true))
	ETurn Turndir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnumClass, Meta = (AllowPrivateAccess = true))
	AimingMode AimState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsMovingOnGround;


	// AnimMontageInstance
	UAnimMontage* RollAnimMontageInstance = nullptr;
};