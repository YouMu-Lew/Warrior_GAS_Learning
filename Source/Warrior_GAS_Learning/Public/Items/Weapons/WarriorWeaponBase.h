// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class WARRIOR_GAS_LEARNING_API AWarriorWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWarriorWeaponBase();

    FORCEINLINE UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }
    FORCEINLINE UBoxComponent* GetWeaponCollisionBox() { return WeaponCollisionBox; }

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Weapons")
    UStaticMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Weapons")
    UBoxComponent* WeaponCollisionBox;
};
