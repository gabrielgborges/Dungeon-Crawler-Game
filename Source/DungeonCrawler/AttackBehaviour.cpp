// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBehaviour.h"

#include <string>

#include "GameFramework/Character.h"
#include "Tasks/GameplayTask_WaitDelay.h"

// Sets default values for this component's properties
UAttackBehaviour::UAttackBehaviour()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackBehaviour::BeginPlay()
{
	Super::BeginPlay();
	
	TObjectPtr<ADungeonCrawlerPlayerController> PlayerController = Cast<ADungeonCrawlerPlayerController>(Character->GetController());
	if(PlayerController)
	{
		CharacterAttributesData = GetOwner()->FindComponentByClass<UCharacterAttributesComponent>();
		if (CharacterAttributesData)
		{
			SetupAttributes();
		}
		
		PlayerController->OnUpdateTarget.AddDynamic(this,&UAttackBehaviour::UpdateTarget);
		PlayerController->OnDie.AddDynamic(this,&UAttackBehaviour::StopAutoAttack);
		UAnimInstance* animInstance = Character->GetMesh()->GetAnimInstance();
		animInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UAttackBehaviour::HandleMontageNotifyStart);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("Could not bind delegates from PlayerController"));

	}
}

void UAttackBehaviour::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UAnimInstance* animInstance = Character->GetMesh()->GetAnimInstance();
	animInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UAttackBehaviour::HandleMontageNotifyStart);
	Super::EndPlay(EndPlayReason);
}

void UAttackBehaviour::SetupAttributes()
{
	if (CharacterAttributesData)
	{
		StrengthAttributeReference = CharacterAttributesData->StrengthAttribute;
		SpeedAttributeReferenceReference = CharacterAttributesData->SpeedAttribute;
		AttackRangeAttributeReference = CharacterAttributesData->AttackRangeAttribute;
	}
}

void UAttackBehaviour::Attack()
{
	IsAttacking = true;
	const float AnimationTime = Character->PlayAnimMontage(AttackAnimation, SpeedAttributeReferenceReference->GetCurrentValue()) / SpeedAttributeReferenceReference->GetCurrentValue();
	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(
		UnusedHandle, this, &UAttackBehaviour::HandleAttackFinished, AnimationTime, false);
	Character->SetActorRotation(Target->GetOwner()->GetActorRotation() * -1);
	if (OnStartAttack.IsBound())
	{
		UE_LOG(LogTemp, Error, TEXT("STARTED ATTACK"));

		OnStartAttack.Broadcast();
	}
}

void UAttackBehaviour::ApplyDamage()
{
	Target->TakeDamage(StrengthAttributeReference->GetCurrentValue());
}

void UAttackBehaviour::TryToAttack()
{
	UE_LOG(LogTemp, Error, TEXT("TRIED TO ATTACK"));

	if(Target == nullptr)
	{
		StopAutoAttack();
	}
	else if(TargetIsInRange() && !Target->IsDead())
	{
		Attack();
	}
	else
	{
		StopAutoAttack();
	}
}

void UAttackBehaviour::HandleAttackFinished()
{
	IsAttacking = false;
	UE_LOG(LogTemp, Error, TEXT("FINISHED ATTACK"));

	if(Target && AutoAttackIsOn && !Target->IsDead())
	{
		UE_LOG(LogTemp, Error, TEXT("Went for next attack"));
		TryToAttack();
	}
}

bool UAttackBehaviour::TargetIsInRange()
{
	if(Target->GetOwner()->GetHorizontalDistanceTo(GetOwner()) <= AttackRangeAttributeReference->GetCurrentValue())
	{
		return true;	
	}
	return false;
}

void UAttackBehaviour::StopAutoAttack()
{
	AutoAttackIsOn = false;
}

void UAttackBehaviour::UpdateTarget(UTakeDamageBehaviour* NewTarget)
{
	Target = NewTarget;
	UE_LOG(LogTemp, Error, TEXT("Tried to update target"));

	if(Target)
	{
		UE_LOG(LogTemp, Error, TEXT("Update target success"));
		AutoAttackIsOn = true;
	}
}

void UAttackBehaviour::HandleMontageNotifyStart(FName notifyName, const FBranchingPointNotifyPayload& notifyPayload)
{
	if (notifyName == "ApplyDamage"){
		ApplyDamage();
	}
}


// Called every frame
void UAttackBehaviour::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(AutoAttackIsOn && !IsAttacking)
	{
		TryToAttack();
	}
}

