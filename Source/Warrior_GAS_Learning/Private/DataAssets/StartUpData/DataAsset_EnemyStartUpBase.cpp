// YouMu All Rights Reserved.

#include "DataAssets/StartUpData/DataAsset_EnemyStartUpBase.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

    if (!EnemyCombatAbilities.IsEmpty()) {
        for (const auto& AbilityClass : EnemyCombatAbilities) {
            if (!AbilityClass) continue;

            FGameplayAbilitySpec AbilitySpec(AbilityClass);
            AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
            AbilitySpec.Level        = ApplyLevel;

            InASCToGive->GiveAbility(AbilitySpec);
        }
    }
}
