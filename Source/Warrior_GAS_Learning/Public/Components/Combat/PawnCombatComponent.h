// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"

#include "GameplayTagContainer.h"

#include "PawnCombatComponent.generated.h"

class AWarriorWeaponBase;

// TODO: 这里为何不定义在 WarriorEnumTypes 里？
UENUM(BlueprintType)
enum class EToggleDamageType : uint8 {
    CurrentEquippedWeapon,
    LeftHand,
    RightHand,
};

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
    FGameplayTag CurrentEquippedWaeponTag;

    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister,
                               bool bRegisterAsEquippedWeapon = false);

    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;

    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    void ToggleWeaponCollision(bool bEnableCollision, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

private:
    TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
};
