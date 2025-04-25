#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindRoamingLocation.generated.h"

UCLASS()
class NPC_AI_API UBTT_FindRoamingLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_FindRoamingLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="Search")
	float SearchRadius = 2000.f;
};