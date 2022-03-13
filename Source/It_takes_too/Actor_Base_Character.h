// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "It_takes_too.h"
#include "GameFramework/Character.h"
#include "Actor_Base_Character.generated.h"

UCLASS()
class IT_TAKES_TOO_API AActor_Base_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActor_Base_Character();
	float GetPressDirection();
	bool GetPressShift();
	bool GetPressCtrl();
	int32 GetPressSpace();
	float GetAngle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EJoomMode
	{
		NORMAL,
		NAILMODE
	};

	void SetControlMode(EJoomMode NewControlMode);
	EJoomMode CurrentControlMode = EJoomMode::NORMAL;
	FVector DirectionToMove = FVector::ZeroVector;
	float ToGoDir;
	float Speedrate;
	float AtoCAngle;
	bool CheckShift;
	bool CheckCtrl;
	int32 CheckSpace;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	virtual void Jump() override;

	void StartSprint();
	void StopSprint();
	void StartWalk();
	void StopWalk();

	void JoomIn();
};
