// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAttributeData.generated.h"

UCLASS()
class DUNGEONCRAWLER_API UCharacterAttributeData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FName AttributeName{};

	UPROPERTY(EditDefaultsOnly)
	float Value{};

public:
	FName GetAttributeName() const { return AttributeName; }

	float GetValue() const { return Value; }
};
