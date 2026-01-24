// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAttributesComponent.h"
#include "CharacterBehaviourBase.h"
#include "DungeonCrawlerPlayerController.h"
#include "Components/ActorComponent.h"
#include "TakeDamageBehaviour.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UTakeDamageBehaviour : public UCharacterBehaviourBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCharacterBehaviourDelegate OnDie;

	UPROPERTY()
	TObjectPtr<UCharacterAttributesComponent> CharacterAttributesData;
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> LifeAttributeReference{};
	UPROPERTY(EditAnywhere)
	ADungeonCrawlerPlayerController* CharacterController;

	UFUNCTION(BlueprintCallable)
	bool IsDead() const {return Died;};
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int32 damage);

	UFUNCTION(BlueprintCallable)
	void Die();

	void HandleAnimationDied();
protected:
	virtual void BeginPlay() override;

	bool Died = false;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* DieAnimation;
	UPROPERTY(EditAnywhere)
	UAnimMontage* TakeDamageAnimation;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
