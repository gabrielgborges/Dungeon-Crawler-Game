// Fill out your copyright notice in the Description page of Project Settings.


#include "TakeDamageBehaviour.h"
#include "GameFramework/Character.h"

void UTakeDamageBehaviour::TakeDamage(int32 damage)
{
	LifeAttributeReference->AddValue(-1 * damage);
	UE_LOG(LogTemp, Log, TEXT("Remaining life is: %f"), LifeAttributeReference->GetCurrentValue());//*GetOwner()->GetInstigator()->Controller->GetName())
	if(LifeAttributeReference->GetCurrentValue() <=0)
	{
		Die();
		return;
	}

	PlayBehaviourAnimation(TakeDamageAnimation);
}

void UTakeDamageBehaviour::Die()
{
	PlayBehaviourAnimation(DieAnimation);
	
	FTimerHandle UnusedHandle;
	float AnimationCompensation = 0.6f;
	GetWorld()->GetTimerManager().SetTimer(
		UnusedHandle, this, &UTakeDamageBehaviour::HandleAnimationDied, Character->PlayAnimMontage(DieAnimation) - AnimationCompensation, false);
	Died = true;
	
	if(CharacterController)
	{
		CharacterController->Die();
	}
	if(OnDie.IsBound())
	{
		OnDie.Broadcast();
	}
}

void UTakeDamageBehaviour::HandleAnimationDied()
{
	Character->GetMesh()->bNoSkeletonUpdate = true;
}

void UTakeDamageBehaviour::BeginPlay()
{
	Super::BeginPlay();
	CharacterController = Cast<ADungeonCrawlerPlayerController>(Character->GetController());
	CharacterAttributesData = GetOwner()->FindComponentByClass<UCharacterAttributesComponent>();
	if (CharacterAttributesData)
	{
		LifeAttributeReference = CharacterAttributesData->LifeAttribute;
	}
	
	if (CharacterController)
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully attatched behaviour"));//*GetOwner()->GetInstigator()->Controller->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Component not added to a Player Controller, to that it will not automatically call its Death behaviour."));
	}
}


void UTakeDamageBehaviour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

