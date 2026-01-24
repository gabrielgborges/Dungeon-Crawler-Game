// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributesComponent.h"

// Sets default values for this component's properties
UCharacterAttributesComponent::UCharacterAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCharacterAttributesComponent::OnRegister()
{
	Super::OnRegister();

	LifeAttribute = NewObject<UCharacterAttributeInstance>(this);
	LifeAttribute->Initialize(LifeAttributeData);
	StrengthAttribute = NewObject<UCharacterAttributeInstance>(this);
	StrengthAttribute->Initialize(StrengthAttributeData);
	SpeedAttribute = NewObject<UCharacterAttributeInstance>(this);
	SpeedAttribute->Initialize(SpeedAttributeData);
	AttackRangeAttribute = NewObject<UCharacterAttributeInstance>(this);
	AttackRangeAttribute->Initialize(AttackRangeAttributeData);
}


// Called every frame
void UCharacterAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

