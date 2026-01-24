// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBehaviourBase.h"

#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCharacterBehaviourBase::UCharacterBehaviourBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterBehaviourBase::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<ACharacter>(GetOwner());	
}

void UCharacterBehaviourBase::PlayBehaviourAnimation(UAnimMontage* Animation)
{
	if(Animation)
	{
		Character->PlayAnimMontage(Animation);
	}
}


// Called every frame
void UCharacterBehaviourBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

