// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarriorGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy : uint8 {
    OnTriggered,
    OnGiven,
};

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UWarriorGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

protected:
    //~ Begin UGameplayAbility Interface.
    /** Called when the ability is given to an AbilitySystemComponent */
    virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilitySpec& Spec) override;
    /** Native function, called if an ability ends normally or abnormally. If bReplicate is set to
     * true, try to replicate the ending to the client/server */
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
                            const FGameplayAbilityActorInfo* ActorInfo,
                            const FGameplayAbilityActivationInfo ActivationInfo,
                            bool bReplicateEndAbility, bool bWasCancelled) override;
    //~ End UGameplayAbility Interface.

    UPROPERTY(EditDefaultsOnly, Category = "WarriorAbility")
    EWarriorAbilityActivationPolicy AbilityActivationPolicy =
        EWarriorAbilityActivationPolicy::OnTriggered;
};
