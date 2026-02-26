// YouMu All Rights Reserved.

#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "WarriorFunctionLibrary.h"

bool UWarriorBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
    if (APawn* Owner = TryGetPawnOwner())
    {
        return UWarriorFunctionLibrary::NativeDoesActorHaveGameplayTag(Owner, TagToCheck);
    }

    return false;
}
