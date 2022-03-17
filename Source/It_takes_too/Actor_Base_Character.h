// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnSprint);

#include "It_takes_too.h"
#include "GameFramework/Character.h"
#include "Actor_Base_Character.generated.h"

UCLASS()
class IT_TAKES_TOO_API AActor_Base_Character : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	// Sets default values for this character's properties
	AActor_Base_Character();
	float GetPressDirection();
	bool GetPressShift();
	bool GetPressCtrl();
	bool GetbIsAimed();
	int32 GetJumpCount();
	float GetAngle();
	// 
	enum class LocomotionState:int8
	{
		Idle,
		Walk,
		Jogging,
		Sprint
	};

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
	LocomotionState LocState;
	AimingMode CurrentAimingMode;
	FOnSprint OnSprint;
	FVector DirectionToMove = FVector::ZeroVector;
	float ToGoDir;			// jogging 때 고개 돌리는 방향
	float Speedrate;		
	FVector AtoCAngle;		// 캐릭터가 바라보는정면 방향과 카메라가 바라보는 정면 방향 사이각
	bool CheckShift;		// 쉬프트키가 눌렸는지 체크
	bool CheckCtrl;			// 컨트롤키가 눌렸는지 체크
	bool bIsAimed;			// 에임이 적용되었는지 체크
	int32 CheckState;

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
	virtual void Jump() override;

	UFUNCTION()
	void EndJump(const FHitResult& Hit);

	void StartSprint();
	void StopSprint();
	void StartWalk();
	void StopWalk();

	void Aim();
	void StopAim();
};
