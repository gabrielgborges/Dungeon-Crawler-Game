// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeInstance.h"

UCharacterAttributeInstance::UCharacterAttributeInstance()
{
}

void UCharacterAttributeInstance::Initialize(TObjectPtr<UCharacterAttributeData> dataAsset)
{
	Attribute = dataAsset;
	if(Attribute)
	{
		CurrentValue = Attribute->GetValue();
	}
}

void UCharacterAttributeInstance::AddValue(float valueToAdd)
{
	CurrentValue += valueToAdd;
	if (OnAttributeUpdate.IsBound())
	{
		OnAttributeUpdate.Broadcast(CurrentValue);
	}
}
