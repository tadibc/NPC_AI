#include "BTT_FindRoamingLocation.h"
#include "AIBoundaryVolume.h"
#include "NavigationSystem.h"
#include "RoamingAICharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FindRoamingLocation::UBTT_FindRoamingLocation()
{
	NodeName = TEXT("Find Roaming Location");
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_FindRoamingLocation, BlackboardKey));
}

EBTNodeResult::Type UBTT_FindRoamingLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if(!AIController) return EBTNodeResult::Failed;

	const ARoamingAICharacter* AICharacter = Cast<ARoamingAICharacter>(AIController->GetPawn());
	if(!AICharacter || !AICharacter->RoamingBoundary) return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIController->GetWorld());
	if(!NavSys) return EBTNodeResult::Failed;

	FNavLocation ResultLocation;
	const FVector RandomPoint = AICharacter->RoamingBoundary->GetRandomPointInVolume();
    
	if(NavSys->GetRandomReachablePointInRadius(RandomPoint, SearchRadius, ResultLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, ResultLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}