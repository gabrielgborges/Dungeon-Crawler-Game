// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAttributeData.h"
#include "CharacterAttributeInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeUpdateDelegate, float, NewValue);
UCLASS(EditInlineNew, DefaultToInstanced)
class DUNGEONCRAWLER_API UCharacterAttributeInstance : public UObject
{
	GENERATED_BODY()

	UCharacterAttributeInstance();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCharacterAttributeData> Attribute{};
	
	UPROPERTY(EditAnywhere)
	float CurrentValue{0};

public:
	UPROPERTY(BlueprintAssignable)
	FAttributeUpdateDelegate OnAttributeUpdate;
	
	void Initialize(TObjectPtr<UCharacterAttributeData> dataAsset);
	
	void AddValue(float valueToAdd);

	inline float GetCurrentValue() const {return CurrentValue;};
	
	inline float GetMaxValue() const {return Attribute->GetValue();};
};
