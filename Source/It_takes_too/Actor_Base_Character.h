// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnSprint);
//DECLARE_DYNAMIC_MULTICAST_del(FCharacterMovementUpdatedSignature);

#include "It_takes_too.h"
#include "GameFramework/Character.h"
#include "Actor_Base_Character.generated.h"

UENUM()
enum class ECharacterState:uint8
{
	Idle,
	Walk,
	Jogging,
	Sprint,
	StopSprint,
	Jump,
	StopJump,	// 점프를 취소한 시점(점프버튼을 뗀 시점)
	Roll,		// 앞구르기
	NormalAiming,	// 기본 에임자세
	WalkAiming,		// 천천히 걷는 에임자세
	Crouch,
	EndCrouch,
	Acquire,	// 못 죄다 수집
	NormalRecall,
	WalkRecall,
	ThrowStart,		// 던시는시점부터 못이 코디한테서 떼질때까지
	ThrowEnd,		// 못이 날아가는와중에 idle로 돌아가는 state
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
	void SetEndRoll();
	// 

	//	 Param :   Velocity,  "PressButton" 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetAimingMode(AimingMode NewAimingMode);
	ECharacterState CharState;
	AimingMode CurrentAimingMode;
	FOnSprint OnSprint;
	FVector DirectionToMove = FVector::ZeroVector;
	float CurrentPawnSpeed;
	float ToGoDir;			// jogging 때 고개 돌리는 방향
	float RotateRate;
	bool IsHoldingWalk;
	bool beCrouched;

	float dot;				// 두 벡터의 내적
	float cross;			// 두 벡터의 외적
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

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void StartJump();
	virtual void Jump() override;
	virtual void StopJumping() override;
	void EndJump();

	void DoCrouch();
	void Roll();

	void StartSprint();
	void StopSprint();
	void StartWalk();
	void StopWalk();

	void Aim();
	void StopAim();

	// input controller 값으로 벡터 산출?   8방향 벡터값
	// 
};
