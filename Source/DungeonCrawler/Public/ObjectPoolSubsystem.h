// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPoolComponent.h"
#include "ObjectPoolConfigDataAsset.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ObjectPool")
	AActor* SpawnObject(UClass* objectClass, FVector spawnLocation, FRotator spawnRotation);
	UFUNCTION(BlueprintCallable, Category = "ObjectPool")
	void DespawnObject(UObjectPoolComponent* objectFromPool);
	
private:
	TMap<UClass*, TArray<TObjectPtr<UObjectPoolComponent>>> objectsInPool;
	UPROPERTY()
	UObjectPoolConfigDataAsset* objectsToSpawnInPool;

	const FString objectPoolConfigPath = "/Game/_DC/DataAssets/ObjectPool/DA_ObjectPool.DA_ObjectPool";
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void InitializePool();
	UFUNCTION()
	void SpawnObjectToPool(UClass* objClass);
};
