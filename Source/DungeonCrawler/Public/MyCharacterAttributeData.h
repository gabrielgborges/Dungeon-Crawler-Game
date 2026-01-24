// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonCrawler/CharacterAttributeData.h"
#include "MyCharacterAttributeData.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UMyCharacterAttributeData : public UCharacterAttributeData
{
	GENERATED_BODY()

	UMyCharacterAttributeData();
	
	UPROPERTY(EditAnywhere)
	UCharacterAttributeData* Attribute{};
};
