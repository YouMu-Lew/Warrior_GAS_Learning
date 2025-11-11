// YouMu All Rights Reserved.

#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"

#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                 AWarriorWeaponBase* InWeaponToRegister,
                                                 bool bRegisterAsEquippedWeapon)
{
    check(InWeaponTagToRegister.IsValid());
    checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),
           TEXT("A tag named %s has already been added as carried weapon."),
           *InWeaponTagToRegister.ToString());

    CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

    if (bRegisterAsEquippedWeapon) {
        CurrentEquippedWaeponTag = InWeaponTagToRegister;
    }

    Debug::Print(FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s."),
                                 *InWeaponToRegister->GetName(),
                                 *InWeaponTagToRegister.ToString()));
}

AWarriorWeaponBase*
UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
    if (InWeaponTagToGet.IsValid() && CharacterCarriedWeaponMap.Contains(InWeaponTagToGet)) {
        return CharacterCarriedWeaponMap.FindRef(InWeaponTagToGet);
    }
    return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
    return GetCharacterCarriedWeaponByTag(CurrentEquippedWaeponTag);
}
