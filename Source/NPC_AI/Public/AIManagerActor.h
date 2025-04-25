// AIManagerActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManagerActor.generated.h"

UCLASS()
class NPC_AI_API AAIManagerActor : public AActor
{
	GENERATED_BODY()

public:
	AAIManagerActor();

	bool IsValidSpawnLocation(FVector Location);
};