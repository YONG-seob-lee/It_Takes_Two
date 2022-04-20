// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnSprint);
//DECLARE_DYNAMIC_MULTICAST_del(FCharacterMovementUpdatedSignature);

#include "../It_takes_too.h"
#include "GameFramework/Character.h"
#include "Actor_Base_Character.generated.h"

UENUM()
enum class ECharacterState:uint8
{
	Idle,
	Walk,
	Jogging,
	Sprint,
	Jump,
	StopJump,	// 점프를 취소한 시점(점프버튼을 뗀 시점)
	Roll,		// 앞구르기
	NormalAiming,	// 기본 에임자세
	WalkAiming,		// 천천히 걷는 에임자세
	JumpAiming,	// 점프 에임자세
	Crouch,
	Acquire,	// 못 죄다 수집
	NormalRecall,
	WalkRecall,
	ThrowStart,		// 던시는시점부터 못이 코디한테서 떼질때까지
	ThrowEnd,		// 못이 날아가는와중에 idle로 돌아가는 state
<<<<<<< HEAD
=======
	Hammering,		// MAY가 해머를 가지고 공격하고있는 state
	NailSwing,		// MAY 못에 해머를 달아 매달리는 State
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
};

UENUM()
enum class ETurn :uint8
{
	Center,
	Right,
	Left
};

UENUM()
enum class AimingMode :uint8
{
	Normal,
	Aiming
};

UCLASS()
class IT_TAKES_TOO_API AActor_Base_Character : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	// Sets default values for this character's properties
	AActor_Base_Character();
	ECharacterState GetState();
	ETurn GetTurnDir();
	float GetPressDirection();
	int32 GetJumpCount();
	float GetAngle();
	float GetSin();
	float GetRotateDirection();
	bool GetDoubleJumped();
	void SetEndRoll();
<<<<<<< HEAD

	AimingMode CurrentAimingMode;
=======
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
	// 

	//	 Param :   Velocity,  "PressButton" 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetAimingMode(AimingMode NewAimingMode);
	ECharacterState CharState;
<<<<<<< HEAD

=======
	AimingMode CurrentAimingMode;
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
	FOnSprint OnSprint;
	FVector DirectionToMove = FVector::ZeroVector;
	float CurrentPawnSpeed;
	float ToGoDir;			// jogging 때 고개 돌리는 방향
	float RotateRate;
	bool IsHoldingWalk;
	bool IsHoldingSprint;
	bool IsDoubleJumped;
	bool beCrouched;

	float dot;				// 두 벡터의 내적
	float cross;			// 두 벡터의 외적
	float RotateDirection;
	ETurn TurnDir;			// 방향성 체크
	float Angle;			// 에임이 적용되었는지 체크
	float SinAngle;
	int32 CheckState;

	FString GetEStateAsString(ECharacterState EnumValue);
	FString GetETurnAtString(ETurn EnumValue);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* CameraBoomNormal;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* CameraBoomAiming;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* FollowingCamera;

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

private:
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	virtual void Jump() override;
	virtual void StopJumping() override;

	UFUNCTION()
	void EndJump(const FHitResult& Hit);

	void DoCrouch();
	void Roll();

	void StartSprint();
	void StopSprint();
	void StartWalk();
	void StopWalk();

	// 
	// 
};
