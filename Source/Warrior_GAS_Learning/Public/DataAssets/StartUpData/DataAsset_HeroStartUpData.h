// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpBase.h"
#include "WarriorTypes/WarriorStructTypes.h"

#include "DataAsset_HeroStartUpData.generated.h"

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpBase
{
    GENERATED_BODY()

public:
    virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
    TArray<FWarriorHeroAbilitySet> HeroAbilitySets;
};
