// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBehaviourBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterBehaviourDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UCharacterBehaviourBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterBehaviourBase();

protected:
	UPROPERTY()
	ACharacter* Character;
	
	virtual void BeginPlay() override;

	void PlayBehaviourAnimation(UAnimMontage* Animation);
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
