// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "WarriorAIController.generated.h"

class UAISenseConfig_Sight;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API AWarriorAIController : public AAIController
{
    GENERATED_BODY()

public:
    AWarriorAIController(const FObjectInitializer& ObjectInitializer);

    //~ Begin UGenericTeamAgentInterface Interface.
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
    //~ End UGenericTeamAgentInterface Interface

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UAIPerceptionComponent* EnemyPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    UAISenseConfig_Sight* EnemySenseConfig_Sight;

    UFUNCTION()
    virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
