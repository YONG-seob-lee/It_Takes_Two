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
	StopJump,	// ������ ����� ����(������ư�� �� ����)
	Roll,		// �ձ�����
	NormalAiming,	// �⺻ �����ڼ�
	WalkAiming,		// õõ�� �ȴ� �����ڼ�
	JumpAiming,	// ���� �����ڼ�
	Crouch,
	Acquire,	// �� �˴� ����
	NormalRecall,
	WalkRecall,
	ThrowStart,		// ���ô½������� ���� �ڵ����׼� ����������
	ThrowEnd,		// ���� ���ư��¿��߿� idle�� ���ư��� state
<<<<<<< HEAD
=======
	Hammering,		// MAY�� �ظӸ� ������ �����ϰ��ִ� state
	NailSwing,		// MAY ���� �ظӸ� �޾� �Ŵ޸��� State
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
	float ToGoDir;			// jogging �� �� ������ ����
	float RotateRate;
	bool IsHoldingWalk;
	bool IsHoldingSprint;
	bool IsDoubleJumped;
	bool beCrouched;

	float dot;				// �� ������ ����
	float cross;			// �� ������ ����
	float RotateDirection;
	ETurn TurnDir;			// ���⼺ üũ
	float Angle;			// ������ ����Ǿ����� üũ
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
