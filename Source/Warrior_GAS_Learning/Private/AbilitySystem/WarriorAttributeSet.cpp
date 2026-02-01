// YouMu All Rights Reserved.

#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
    InitCurrentHealth(0.f);
    InitMaxHealth(0.f);
    InitCurrentRage(0.f);
    InitMaxRage(0.f);
    InitAttackPower(0.f);
    InitDefensePower(0.f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    const auto& Attribute = Data.EvaluatedData.Attribute;
    if (Attribute == GetCurrentHealthAttribute()) {
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
    } else if (Attribute == GetCurrentRageAttribute()) {
        SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));
    } else if (Attribute == GetDamageTakenAttribute()) {
        const auto OldHealth = GetCurrentHealth();
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - GetDamageTaken(), 0.f, GetMaxHealth()));

        //Debug::Print(
        //    FString::Printf(TEXT("Old Health: %f\nDamage Taken: %f\nCur Health: %f"), OldHealth, GetDamageTaken(), GetCurrentHealth()),
        //    FColor::Red);

        // TODO: Notify the UI

        if (GetCurrentHealth() <= 0.f) {
            UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dealth);
        }
    }
}
