// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"

#include "DataAssets/Input/DataAsset_InputConfig.h"

#include "WarriorInputComponent.generated.h"

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UWarriorInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

public:
    template <class UserObject, typename CallbackFunc>
    inline void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
                                      ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

    template <class UserObject, typename CallbackFunc>
    inline void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
                                       CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, typename CallbackFunc>
inline void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag,
                                                          ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
    checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding."));

    if (auto FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag)) {
        BindAction(FoundAction, TriggerEvent, ContextObject, Func);
    }
}

template <class UserObject, typename CallbackFunc>
inline void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject,
                                                           CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
    checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding."));

    for (const FWarriorInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions) {
        if (!AbilityInputActionConfig.IsValid()) continue;

        BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc,
                   AbilityInputActionConfig.InputTag);
        BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc,
                   AbilityInputActionConfig.InputTag);
    }
}
