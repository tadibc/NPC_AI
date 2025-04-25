#include "LandscapeAISpawner.h"
#include "RoamingAICharacter.h"
#include "NavigationSystem.h"
#include "Landscape.h"
#include "DrawDebugHelpers.h"

ALandscapeAISpawner::ALandscapeAISpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALandscapeAISpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnAI();  // This calls the private SpawnAI function
}

// Implement the missing SpawnAI function
void ALandscapeAISpawner::SpawnAI()
{
	if (!AIClass || !SpawnBoundary)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing AIClass or SpawnBoundary!"));
		return;
	}

	int32 SuccessfulSpawns = 0;
	const int32 MaxAttempts = SpawnCount * 10;

	for (int32 i = 0; i < MaxAttempts && SuccessfulSpawns < SpawnCount; ++i)
	{
		FVector SpawnLocation;
		if (FindValidSpawnLocation(SpawnLocation))
		{
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = 
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			if (GetWorld()->SpawnActor<ARoamingAICharacter>(AIClass, SpawnLocation, FRotator::ZeroRotator, Params))
			{
				SuccessfulSpawns++;
			}
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Successfully spawned %d AI characters"), SuccessfulSpawns);
}

bool ALandscapeAISpawner::FindValidSpawnLocation(FVector& OutLocation)
{
	if (!SpawnBoundary) return false;

	UWorld* World = GetWorld();
	if (!World) return false;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (!NavSys) return false;

	for (int32 i = 0; i < 25; i++)
	{
		FVector RandomPoint = SpawnBoundary->GetRandomPointInVolume();
		FNavLocation NavLocation;

		if (NavSys->ProjectPointToNavigation(RandomPoint, NavLocation))
		{
			FHitResult HitResult;
			FVector TraceStart = NavLocation.Location + FVector(0, 0, 1000);
			FVector TraceEnd = NavLocation.Location - FVector(0, 0, 1000);

			if (World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility))
			{
				if (HitResult.GetComponent() && 
					HitResult.GetComponent()->IsA(ULandscapeHeightfieldCollisionComponent::StaticClass()))
				{
					FVector Normal = HitResult.ImpactNormal;
					float SlopeAngle = FMath::RadiansToDegrees(FMath::Acos(Normal.Z));
                    
					if (SlopeAngle <= 45.0f)
					{
						OutLocation = HitResult.Location + FVector(0, 0, 120.0f);
                        
						if (!AIManager || AIManager->IsValidSpawnLocation(OutLocation))
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}