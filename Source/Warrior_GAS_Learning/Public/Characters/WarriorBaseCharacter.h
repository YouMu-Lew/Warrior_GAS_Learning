// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WarriorBaseCharacter.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorAttributeSet;

UCLASS()
class WARRIOR_GAS_LEARNING_API AWarriorBaseCharacter : public ACharacter,
                                                       public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AWarriorBaseCharacter();

    //~ Begin APawn Interface.
    virtual void PossessedBy(AController* NewController) override;
    //~ End APawn Interface

    //~ Begin IAbilitySystemInterface Interface.
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //~ End IAbilitySystemInterface Interface

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    UWarriorAbilitySystemComponent* WarriorAbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    UWarriorAttributeSet* WarriorAttributeSet;

public:
    FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const
    {
        return WarriorAbilitySystemComponent;
    }

    FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
};
