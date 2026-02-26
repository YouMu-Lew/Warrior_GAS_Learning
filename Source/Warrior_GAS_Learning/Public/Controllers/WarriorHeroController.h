// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"

#include "WarriorHeroController.generated.h"

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API AWarriorHeroController : public APlayerController, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

public:
    AWarriorHeroController();

    //~ Begin UGenericTeamAgentInterface Interface.
    virtual FGenericTeamId GetGenericTeamId() const override;
    //~ End UGenericTeamAgentInterface Interface

protected:
    FGenericTeamId HeroTeamId;
};
