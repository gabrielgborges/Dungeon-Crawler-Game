// Fill out your copyright notice in the Description page of Project Settings.


//#include "HealthBarComponent.h"
#include "DungeonCrawler/Public/HealthBarComponent.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (LifeAttribute != nullptr)
	{
		LifeAttribute->OnAttributeUpdate.RemoveDynamic(this, &UHealthBarComponent::CalculatePercentageHP);
	}
}

// Sets default values for this component's properties
UHealthBarComponent::UHealthBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UHealthBarComponent::CalculatePercentageHP(float newValue)
{
	if (!LifeAttribute || !HealthProgressBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("LifeAttribute or HealthProgressBar is null"));
		return;
	}

	float percentage = newValue/LifeAttribute->GetMaxValue();
	HealthProgressBar->SetPercent(percentage);
}

void UHealthBarComponent::Initialize(UProgressBar* healthBar, UCharacterAttributesComponent* healthAttribute)
{
	HealthProgressBar = healthBar;
	AttributesData = healthAttribute;
	
	if (AttributesData && HealthProgressBar)
	{
		LifeAttribute = AttributesData->LifeAttribute;
		if (LifeAttribute != nullptr)
		{
			CalculatePercentageHP(LifeAttribute->GetCurrentValue());
			LifeAttribute->OnAttributeUpdate.AddDynamic(this, &UHealthBarComponent::CalculatePercentageHP);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UCharacterAttributesComponent/Progress Bar not found to setup health bar script"));
	}
}