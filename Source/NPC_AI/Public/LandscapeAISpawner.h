#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManagerActor.h"
#include "AIBoundaryVolume.h"
#include "LandscapeAISpawner.generated.h"

UCLASS()
class NPC_AI_API ALandscapeAISpawner : public AActor
{
	GENERATED_BODY()

public:
	ALandscapeAISpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<class ARoamingAICharacter> AIClass;

	UPROPERTY(EditAnywhere, Category="Spawning", meta=(ClampMin="1"))
	int32 SpawnCount = 5;

	UPROPERTY(EditAnywhere, Category="Spawning")
	AAIManagerActor* AIManager;

	UPROPERTY(EditAnywhere, Category="Spawning")
	AAIBoundaryVolume* SpawnBoundary;

private:
	void SpawnAI();  // Declaration
	bool FindValidSpawnLocation(FVector& OutLocation);
};