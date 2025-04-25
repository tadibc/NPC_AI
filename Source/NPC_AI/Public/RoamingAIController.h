#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RoamingAIController.generated.h"

UCLASS()
class NPC_AI_API ARoamingAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARoamingAIController();

	UPROPERTY(EditDefaultsOnly, Category="AI")
	class UBehaviorTree* BehaviorTree;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent;
};