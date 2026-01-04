// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AWarriorHeroWeapon;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UHeroCombatComponent : public UPawnCombatComponent
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
    AWarriorHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};
