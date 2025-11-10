// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WARRIOR_GAS_LEARNING_API UPawnExtensionComponentBase : public UActorComponent
{
    GENERATED_BODY()

protected:
    template <class T = APawn>
    T* GetOwningPawn() const
    {
        static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value,
                      "'T' Template Parameter to GetPawn must be derived from APawn.");
        return CastChecked<T>(GetOwner());
    }

    template <class T>
    T* GetOwningController() const
    {
        static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,
                      "'T' Template Parameter to GetController must be derived from AController.");
        return GetOwningPawn()->GetController<T>();
    }
};
