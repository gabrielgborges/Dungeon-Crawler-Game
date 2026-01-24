// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DungeonCrawler/CharacterAttributeInstance.h"
#include "CharacterAttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UCharacterAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterAttributesComponent();

	UPROPERTY(EditAnywhere, Category="Attributes")
	TObjectPtr<UCharacterAttributeData> LifeAttributeData{};
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> LifeAttribute{};
	UPROPERTY(EditAnywhere, Category="Attributes")
	TObjectPtr<UCharacterAttributeData> StrengthAttributeData{};
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> StrengthAttribute{};
	UPROPERTY(EditAnywhere, Category="Attributes")
	TObjectPtr<UCharacterAttributeData> SpeedAttributeData{};
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> SpeedAttribute{};
	UPROPERTY(EditAnywhere, Category="Attributes")
	TObjectPtr<UCharacterAttributeData> AttackRangeAttributeData{};
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> AttackRangeAttribute{};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
