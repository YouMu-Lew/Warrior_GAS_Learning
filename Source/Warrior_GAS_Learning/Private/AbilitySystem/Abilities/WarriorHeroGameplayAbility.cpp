// YouMu All Rights Reserved.

#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!_CachedHeroCharacter.IsValid()) {
        _CachedHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
    }

    return _CachedHeroCharacter.IsValid() ? _CachedHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!_CachedHeroController.IsValid()) {
        _CachedHeroController = Cast<AWarriorHeroController >(CurrentActorInfo->PlayerController);
    }

    return _CachedHeroController.IsValid() ? _CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
