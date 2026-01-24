// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ObjectPoolConfigDataAsset.generated.h"

USTRUCT()
struct FObjectPoolSpec
{
	GENERATED_BODY()
public:
	inline TSubclassOf<AActor> GetClass () const { return ActorClass;};
	inline int32 GetPrewarmCount () const { return PrewarmCount;};
	inline bool GetUnlimitedSpawn () const { return UnlimitedSpawn;};
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClass;
	UPROPERTY(EditAnywhere)
	int32 PrewarmCount = 0;
	UPROPERTY(EditAnywhere)
	bool UnlimitedSpawn = false;
};

UCLASS()
class DUNGEONCRAWLER_API UObjectPoolConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FObjectPoolSpec> PoolSpecs;
};
