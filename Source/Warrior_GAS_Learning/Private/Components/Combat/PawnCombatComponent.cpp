// YouMu All Rights Reserved.

#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister,
                                                 bool bRegisterAsEquippedWeapon)
{
    check(InWeaponTagToRegister.IsValid());
    checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A tag named %s has already been added as carried weapon."),
           *InWeaponTagToRegister.ToString());

    CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

    if (bRegisterAsEquippedWeapon) {
        CurrentEquippedWaeponTag = InWeaponTagToRegister;
    }
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
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

void UPawnCombatComponent::ToggleWeaponCollision(bool bEnableCollision, EToggleDamageType ToggleDamageType)
{
    if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon) {
        AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

        check(WeaponToToggle);

        if (bEnableCollision) {
            WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        } else {
            WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }

    // TODO: Handle body collision boxes
}
