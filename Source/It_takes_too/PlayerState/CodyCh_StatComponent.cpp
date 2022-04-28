// Fill out your copyright notice in the Description page of Project Settings.


#include "CodyCh_StatComponent.h"
#include "../Instance/ITT_Instance.h"
#include "../Data/CharacterData.h"

// Sets default values for this component's properties
UCodyCh_StatComponent::UCodyCh_StatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void UCodyCh_StatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCodyCh_StatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UCodyCh_StatComponent::SetNewLevel(int32 NewLevel)
{
	UITT_Instance* ITT_Instance = Cast<UITT_Instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr == ITT_Instance)	return;

	CurrentStatData = ITT_Instance->GetActorData(NewLevel);
	if (CurrentStatData) {
		Level = NewLevel;
		CurrentHP = CurrentStatData->MaxHP;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Level %d data doesn't exist."), NewLevel);
	}
}

float UCodyCh_StatComponent::GetAttack()
{
	if (nullptr == CurrentStatData) return 0.0f;

	else	return CurrentStatData->Attack;
}


// Called every frame
void UCodyCh_StatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

