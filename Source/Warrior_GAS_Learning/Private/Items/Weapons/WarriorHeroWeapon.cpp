// YouMu All Rights Reserved.

#include "Items/Weapons/WarriorHeroWeapon.h"

void AWarriorHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
    GrantedAbilitySpecHandles = InSpecHandles;
}

const TArray<FGameplayAbilitySpecHandle>& AWarriorHeroWeapon::GetGrantedAbilitySpecHandles() const
{
    return GrantedAbilitySpecHandles;
}
