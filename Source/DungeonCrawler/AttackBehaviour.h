// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TakeDamageBehaviour.h"
#include "AttackBehaviour.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackBehaviourDelegate);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UAttackBehaviour : public UCharacterBehaviourBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackBehaviour();

protected:
	UPROPERTY(BlueprintAssignable)
	FAttackBehaviourDelegate OnStartAttack;
	
	UPROPERTY()
	TObjectPtr<UCharacterAttributesComponent> CharacterAttributesData{};
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> StrengthAttributeReference{};
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> SpeedAttributeReferenceReference{};
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> AttackRangeAttributeReference{};
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnimation;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UTakeDamageBehaviour* Target{nullptr};

	bool AutoAttackIsOn = false;
	
	bool IsAttacking = false;

	void SetupAttributes();
	
	void Attack();
	
	void ApplyDamage();
	
	void TryToAttack();

	void HandleAttackFinished();

	bool TargetIsInRange();

	UFUNCTION()
	void StopAutoAttack();

	UFUNCTION()
	void UpdateTarget(UTakeDamageBehaviour* NewTarget);

	UFUNCTION()
	void HandleMontageNotifyStart(FName notifyName, const FBranchingPointNotifyPayload& notifyPayload);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
