#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIBoundaryVolume.h"
#include "RoamingAICharacter.generated.h"

UCLASS()
class NPC_AI_API ARoamingAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARoamingAICharacter();

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess="true"))
	AAIBoundaryVolume* RoamingBoundary;*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	AAIBoundaryVolume* RoamingBoundary;

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;
};