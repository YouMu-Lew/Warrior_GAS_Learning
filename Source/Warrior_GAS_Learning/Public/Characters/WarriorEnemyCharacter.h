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
    AWarriorEnemyCharacter();

    FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    UEnemyCombatComponent* EnemyCombatComponent;
};
