// YouMu All Rights Reserved.

#include "AbilitySystem/WarriorAttributeSet.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
    InitCurrentHealth(100.f);
    InitMaxHealth(100.f);
    InitCurrentRage(0.f);
    InitMaxRage(100.f);
    InitAttackPower(20.f);
    InitDefensePower(10.f);
}
