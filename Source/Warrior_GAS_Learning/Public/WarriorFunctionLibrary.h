// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"

#include "WarriorFunctionLibrary.generated.h"

class UWarriorAbilitySystemComponent;

UENUM()
enum class EWarriorConfirmType : uint8 {
    Yes,
    No,
};

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

    UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
    static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

    UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
    static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

    static bool NativeDoesActorHaveGameplayTag(AActor* InActor, FGameplayTag TagToCheck);

    UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary",
              meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
    static void BP_DoesActorHaveGameplayTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType);
};
