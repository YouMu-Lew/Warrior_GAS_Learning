// YouMu All Rights Reserved.

#include "Controllers/WarriorAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

#include "WarriorDebugHelper.h"

AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
    auto CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
    if (CrowdFollowingComponent)
    {
        Debug::Print("TEXT TODO: CrowdFollowingComponent created successfully.", FColor::Green);
    }

    EnemySenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySenseConfig_Sight"));
    EnemySenseConfig_Sight->DetectionByAffiliation.bDetectEnemies    = true;
    EnemySenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
    EnemySenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals   = false;
    EnemySenseConfig_Sight->SightRadius                              = 5000.0f;
    EnemySenseConfig_Sight->LoseSightRadius                          = 0.f;
    EnemySenseConfig_Sight->PeripheralVisionAngleDegrees             = 360.f;

    EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
    EnemyPerceptionComponent->ConfigureSense(*EnemySenseConfig_Sight);
    EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
    EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

    SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    auto PawnToCheck = CastChecked<const APawn>(&Other);

    auto OtherTeamAgentInterface = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

    if (OtherTeamAgentInterface && OtherTeamAgentInterface->GetGenericTeamId() != GetGenericTeamId())
    {
        return ETeamAttitude::Hostile;
    }

    return ETeamAttitude::Friendly;
}

void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Stimulus.WasSuccessfullySensed() && Actor)
    {
        Debug::Print(FString::Printf(TEXT("Enemy %s sensed."), *Actor->GetName()), FColor::Red);
    }
}
