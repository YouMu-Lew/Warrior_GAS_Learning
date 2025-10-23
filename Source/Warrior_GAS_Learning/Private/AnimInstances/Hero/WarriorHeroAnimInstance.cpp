// YouMu All Rights Reserved.

#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"
#include "Characters/WarriorHeroCharacter.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (OwningCharacter) {
        OwningHeroCharacter = Cast<AWarriorHeroCharacter>(OwningCharacter);
    }
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

    if (bHasAcceleration) {
        IdleElapsedTime        = 0.f;
        bShouldEnterRelaxState = false;
    } else {
        IdleElapsedTime += DeltaSeconds;
        // Max Value
        if (IdleElapsedTime >= FLT_MAX / 2.f) {
            IdleElapsedTime = FLT_MAX / 2.f;
        }
        bShouldEnterRelaxState = IdleElapsedTime >= EnterRelaxStateThreshold;
    }
}
