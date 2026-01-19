// YouMu All Rights Reserved.

#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Characters/WarriorEnemyCharacter.h"

AWarriorEnemyCharacter* UWarriorEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
    if (!_CachedEnemyCharacter.IsValid()) {
        _CachedEnemyCharacter = Cast<AWarriorEnemyCharacter>(CurrentActorInfo->AvatarActor);
    }
    return _CachedEnemyCharacter.IsValid() ? _CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UWarriorEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
    const AWarriorEnemyCharacter* EnemyChar = GetEnemyCharacterFromActorInfo();
    if (!EnemyChar) {
        UE_LOG(LogTemp, Warning, TEXT("GetEnemyCombatComponentFromActorInfo: Enemy character is null for ability %s"), *GetName());
        return nullptr;
    }

    return EnemyChar->GetEnemyCombatComponent(); 
}
