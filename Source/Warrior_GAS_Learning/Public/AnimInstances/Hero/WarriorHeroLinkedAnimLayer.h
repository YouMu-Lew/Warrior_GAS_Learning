// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "WarriorHeroLinkedAnimLayer.generated.h"

class UWarriorHeroAnimInstance;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UWarriorHeroLinkedAnimLayer : public UWarriorBaseAnimInstance
{
    GENERATED_BODY()

public:
    // 为了在蓝图中通过 property access 访问，必须标记 BlueprintPure 和 BlueprintThreadSafe
    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    UWarriorHeroAnimInstance* GetHeroAnimInstance() const;
};
