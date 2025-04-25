#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AIBoundaryVolume.generated.h"

UCLASS(Blueprintable, BlueprintType)
class NPC_AI_API AAIBoundaryVolume : public AActor
{
	GENERATED_BODY()
    
public:
	AAIBoundaryVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Boundary")
	UBoxComponent* BoundaryBox;

	UFUNCTION(BlueprintCallable, Category="Boundary")
	FVector GetRandomPointInVolume() const;
};