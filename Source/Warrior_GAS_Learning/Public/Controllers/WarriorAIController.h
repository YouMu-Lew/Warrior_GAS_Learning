// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/CrowdFollowingComponent.h"

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

    //~ Begin AActor Interface.
    virtual void BeginPlay() override;
    //~ End AActor Interface

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

private:
    UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
    bool bEnableDetourCrowdAvoidance;

    UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config",
              meta = (EditCondition = "bEnableDetourCrowdAvoidance", ClampMin = "1", ClampMax = "4"))
    uint32 DetourCrowdAvoidanceQuality;

    UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance"))
    float CollisionQueryRange;
};
