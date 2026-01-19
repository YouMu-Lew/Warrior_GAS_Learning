// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpBase.h"
#include "DataAsset_EnemyStartUpBase.generated.h"

class UWarriorEnemyGameplayAbility;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UDataAsset_EnemyStartUpBase : public UDataAsset_StartUpBase
{
    GENERATED_BODY()

public:
    virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
    TArray<TSubclassOf<UWarriorEnemyGameplayAbility>> EnemyCombatAbilities;
};
