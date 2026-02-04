// YouMu All Rights Reserved.

#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"

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
    if (!CachedPawnUIInterface.IsValid())
    {
        CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
    }

    checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface."),
           *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

    UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

    checkf(PawnUIComponent, TEXT("Couldn't extrac a PawnUIComponent from %s."), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

    const auto& Attribute = Data.EvaluatedData.Attribute;
    if (Attribute == GetCurrentHealthAttribute())
    {
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));

        PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
    }
    else if (Attribute == GetCurrentRageAttribute())
    {
        SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));

        if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
        {
            HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
        }
    }
    else if (Attribute == GetDamageTakenAttribute())
    {
        const auto OldHealth = GetCurrentHealth();
        SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - GetDamageTaken(), 0.f, GetMaxHealth()));

        // TODO: Notify the UI

        if (GetCurrentHealth() <= 0.f)
        {
            UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Death);
        }
    }
}
