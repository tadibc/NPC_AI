#include "RoamingAICharacter.h"
#include "AIBoundaryVolume.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"

ARoamingAICharacter::ARoamingAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARoamingAICharacter::BeginPlay()
{
	Super::BeginPlay();
	/*if(!RoamingBoundary)
	{
		UE_LOG(LogTemp, Fatal, TEXT("RoamingBoundary is not assigned!"));
	}*/
}

void ARoamingAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AAIController* AIController = Cast<AAIController>(GetController());
	if(AIController && AIController->GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		if(RoamingBoundary)
		{
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
			if(NavSys)
			{
				FNavLocation RandomNavLocation;
				FVector RandomPoint = RoamingBoundary->GetRandomPointInVolume();
                
				if(NavSys->GetRandomReachablePointInRadius(RandomPoint, 2000.f, RandomNavLocation))
				{
					AIController->MoveToLocation(RandomNavLocation.Location);
					DrawDebugSphere(GetWorld(), RandomNavLocation.Location, 50.f, 12, FColor::Green, false, 2.f);
				}
			}
		}
	}
}