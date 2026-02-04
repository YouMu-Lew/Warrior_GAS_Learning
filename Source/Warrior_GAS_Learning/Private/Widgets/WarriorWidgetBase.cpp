// YouMu All Rights Reserved.

#include "Widgets/WarriorWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

void UWarriorWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
    if (auto PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
    {
        auto EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

        checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s."), *OwningEnemyActor->GetActorNameOrLabel());

        BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
    }
}

void UWarriorWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (auto PawnUIInterface = GetOwningPlayerPawn<IPawnUIInterface>())
    {
        if (auto HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
        {
            BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
        }
    }
}
