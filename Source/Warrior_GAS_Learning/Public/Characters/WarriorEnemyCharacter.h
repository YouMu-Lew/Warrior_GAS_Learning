// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"

#include "WarriorEnemyCharacter.generated.h"

class UEnemyCombatComponent;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API AWarriorEnemyCharacter : public AWarriorBaseCharacter
{
    GENERATED_BODY()

public:
    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface

    AWarriorEnemyCharacter();

    FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UEnemyCombatComponent* EnemyCombatComponent;

private:
    /**
     * 异步加载敌人角色的启动数据
     */
    void InitEnemyStartUpData();
};
