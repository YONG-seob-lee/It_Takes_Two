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
	StopJump,	// ������ ����� ����(������ư�� �� ����)
	Roll,		// �ձ�����
	NormalAiming,	// �⺻ �����ڼ�
	WalkAiming,		// õõ�� �ȴ� �����ڼ�
	ThrowStart,		// ���ô½������� ���� �ڵ����׼� ����������
	ThrowEnd,		// ���� ���ư��¿��߿� idle�� ���ư��� state
	Acquire,	// �� �˴� ����
	NormalRecall,
	WalkRecall,
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
	float GetPressDirection();
	bool GetbIsAimed();
	int32 GetJumpCount();
	float GetAngle();
	// 

	//	 Param :   Velocity,  "PressButton" 
	enum class AimingMode
	{
		Normal,
		Aiming
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetAimingMode(AimingMode NewAimingMode);
	ECharacterState CharState;
	AimingMode CurrentAimingMode;
	FOnSprint OnSprint;
	FVector DirectionToMove = FVector::ZeroVector;
	float CurrentPawnSpeed;
	float ToGoDir;			// jogging �� �� ������ ����
	float Speedrate;		

	float dot;			// �� ������ ����
	float Angle;		// ĳ���Ͱ� �ٶ󺸴����� ����� ī�޶� �ٶ󺸴� ���� ���� ���̰�
	bool bIsAimed;			// ������ ����Ǿ����� üũ
	int32 CheckState;

	FString GetEStateAsString(ECharacterState EnumValue);

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

	void StartSprint();
	void StopSprint();
	void StartWalk();
	void StopWalk();

	void Aim();
	void StopAim();

	// input controller ������ ���� ����?   8���� ���Ͱ�
	// 
};
