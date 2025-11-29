// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpBase.generated.h"

class UWarriorGameplayAbility;
class UWarriorAbilitySystemComponent;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UDataAsset_StartUpBase : public UDataAsset
{
    GENERATED_BODY()

public:
    virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
    TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
    TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

protected:
    void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive, UWarriorAbilitySystemComponent* InASCToGive,
                        int32 ApplyLevel);
};
