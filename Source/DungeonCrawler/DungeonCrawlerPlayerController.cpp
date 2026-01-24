// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonCrawlerPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TakeDamageBehaviour.h"
#include "GameFramework/Character.h"

ADungeonCrawlerPlayerController::ADungeonCrawlerPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	cachedDestination = FVector::ZeroVector;
	followTime = 0.f;
}

void ADungeonCrawlerPlayerController::Die() 
{
	if(OnDie.IsBound())
	{
		OnDie.Broadcast();
	}
	DisableInput(this);
}

void ADungeonCrawlerPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ADungeonCrawlerPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADungeonCrawlerPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADungeonCrawlerPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADungeonCrawlerPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADungeonCrawlerPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ADungeonCrawlerPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ADungeonCrawlerPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ADungeonCrawlerPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ADungeonCrawlerPlayerController::OnTouchReleased);
	}
}

void ADungeonCrawlerPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ADungeonCrawlerPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	followTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitGroundSuccessful = false;
	bool isTargetingItself = false;
	bool bHitEnemySuccessful = 	GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel10, true, Hit);//can use ByChannel as well
	UActorComponent* TakeDamageComponent = Hit.GetActor()->GetComponentByClass(UTakeDamageBehaviour::StaticClass());
	UE_LOG(LogTemp, Error, TEXT("DaleMeia %s and it is %s"),*Hit.GetActor()->GetName(), bHitEnemySuccessful ? TEXT("true") : TEXT("false"));
	if(TakeDamageComponent)
	{
		uint32 a = TakeDamageComponent->GetOwner()->GetUniqueID();
		if (GetCharacter())
		{
			uint32 b = GetCharacter()->GetUniqueID();
		
			UE_LOG(LogTemp, Error, TEXT("Comparsion with target and attacker %i and %i"),a, b );
			isTargetingItself = (a == b);
		}
	}
	
	if(bHitEnemySuccessful && TakeDamageComponent && !isTargetingItself)
	{
		OnUpdateTarget.Broadcast(Cast<UTakeDamageBehaviour>(TakeDamageComponent));
	}
	
	if (bIsTouch)
	{
		bHitGroundSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitGroundSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (TakeDamageComponent)
	{
		cachedDestination = TakeDamageComponent->GetOwner()->GetActorLocation();
	}
	else if (bHitGroundSuccessful)
	{
		cachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (cachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ADungeonCrawlerPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (followTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, cachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, cachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	followTime = 0.f;
}

// Triggered every frame when the input is held down
void ADungeonCrawlerPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ADungeonCrawlerPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
