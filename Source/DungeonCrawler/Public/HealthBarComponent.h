// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DungeonCrawler/CharacterAttributeInstance.h"
#include "CharacterAttributesComponent.h"
#include "HealthBarComponent.generated.h"

class UProgressBar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UHealthBarComponent : public UActorComponent
{
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthBarComponent();
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UCharacterAttributesComponent> AttributesData;
	UPROPERTY()
	TObjectPtr<UCharacterAttributeInstance> LifeAttribute{};
	UPROPERTY()
	UProgressBar* HealthProgressBar;

	UFUNCTION()
	void CalculatePercentageHP(float newValue);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Initialize(UProgressBar* healthBar, UCharacterAttributesComponent* healthAttribute);

};
