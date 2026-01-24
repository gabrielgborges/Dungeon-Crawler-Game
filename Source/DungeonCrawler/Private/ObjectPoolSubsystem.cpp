// Fill out your copyright notice in the Description page of Project Settings.
#include "ObjectPoolSubsystem.h"
#include "ObjectPoolComponent.h"
#include "Engine/World.h"

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitializePool();
}

AActor* UObjectPoolSubsystem::SpawnObject(UClass* objectClass, FVector spawnLocation, FRotator spawnRotation = FRotator(0, 0, 0))
{
	if (objectsInPool.Contains(objectClass))
	{
		for (TObjectPtr<UObjectPoolComponent> objectInPool: objectsInPool[objectClass])
		{
			if (!objectInPool->inUse)
			{
				objectInPool->GetOwner()->SetActorLocationAndRotation(spawnLocation, spawnRotation);
				objectInPool->OnSpawn();
				UE_LOG(LogTemp, Warning, TEXT("Spawned %s successfully!"), *objectInPool->GetName());

				return objectInPool->GetOwner();
			}
		}
	}

	return nullptr;
}

void UObjectPoolSubsystem::DespawnObject(UObjectPoolComponent* objectFromPool)
{
	UClass* objectOwnerClass = objectFromPool->GetOwner()->GetClass();
	for ( TObjectPtr<UObjectPoolComponent> objectInPool: objectsInPool[objectOwnerClass])
	{
		if (objectFromPool == objectInPool)
		{
			UE_LOG(LogTemp, Warning, TEXT("Got it"));
	
			objectFromPool->OnDespawn();
			return;
		}
	}
}

void UObjectPoolSubsystem::InitializePool()
{
	const FSoftObjectPath dataPath(objectPoolConfigPath);
	objectsToSpawnInPool = Cast<UObjectPoolConfigDataAsset>(dataPath.TryLoad());

	if (objectsToSpawnInPool)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found it!"));

		for (FObjectPoolSpec objData : objectsToSpawnInPool->PoolSpecs)
		{
			int counter = 0;
			while (counter < objData.GetPrewarmCount())
			{
				SpawnObjectToPool(objData.GetClass());
				counter++;
			}
		}
	}
}

void UObjectPoolSubsystem::SpawnObjectToPool(UClass* objClass)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = nullptr;
	spawnParams.Instigator = nullptr;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(
		objClass,
		FVector(0, 0, 0),
		FRotator(0, 0, 0),
		spawnParams
	);

	if (spawnedActor)
	{
		TObjectPtr<UObjectPoolComponent> objectPoolComponent = spawnedActor->GetComponentByClass<UObjectPoolComponent>();	
		
		if (objectPoolComponent)
		{
			objectPoolComponent->Initialize();
			if (objectsInPool.Contains(objClass))
			{
				objectsInPool[objClass].Add(objectPoolComponent);
				UE_LOG(LogTemp, Warning, TEXT("Added to new pool"));
			}
			else
			{
				objectsInPool.Add(objClass, TArray<TObjectPtr<UObjectPoolComponent>>{objectPoolComponent});
				UE_LOG(LogTemp, Warning, TEXT("Added to old pool"));
			}
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Spawned %s successfully!"), *spawnedActor->GetName());
	}
}