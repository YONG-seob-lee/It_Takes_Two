// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
#include "GameFramework/PlayerController.h"
#include "../Character/Actor_CodyCh.h"
#include "FirstPlayerController.generated.h"

/**
 *
 */
UCLASS()
class IT_TAKES_TOO_API AFirstPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFirstPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	bool IsAimed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UCody_Widget>UI_Class;

	class UCody_Widget* CodyUI_Object;

	AActor_CodyCh* Owner = nullptr;
	void GetBind(AActor_CodyCh* Target);
};
