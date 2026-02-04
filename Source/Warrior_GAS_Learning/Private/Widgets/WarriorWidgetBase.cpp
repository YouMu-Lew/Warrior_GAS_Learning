// YouMu All Rights Reserved.

#include "Widgets/WarriorWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

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
