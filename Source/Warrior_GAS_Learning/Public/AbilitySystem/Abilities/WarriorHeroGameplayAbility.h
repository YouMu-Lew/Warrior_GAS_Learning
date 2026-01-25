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

    /**
     * 可根据需求自定义参数的伤害效果规格句柄生成函数
     */
    UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
    FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> DamageEffectClass, float InWeaponBaseDamage,
                                                             FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

private:
    TWeakObjectPtr<AWarriorHeroCharacter> _CachedHeroCharacter;
    TWeakObjectPtr<AWarriorHeroController> _CachedHeroController;
};
