// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"

#include "WarriorHeroGameplayAbility.generated.h"

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    AWarriorHeroCharacter* GetHeroCharacterFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    AWarriorHeroController* GetHeroControllerFromActorInfo();

    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
    TWeakObjectPtr<AWarriorHeroCharacter> _CachedHeroCharacter;
    TWeakObjectPtr<AWarriorHeroController> _CachedHeroController;
};
