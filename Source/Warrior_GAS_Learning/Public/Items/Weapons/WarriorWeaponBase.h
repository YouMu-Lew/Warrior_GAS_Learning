// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

UCLASS()
class WARRIOR_GAS_LEARNING_API AWarriorWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AWarriorWeaponBase();

    FORCEINLINE UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }
    FORCEINLINE UBoxComponent* GetWeaponCollisionBox() { return WeaponCollisionBox; }

    FOnTargetInteractedDelegate OnWeaponHitTarget;
    FOnTargetInteractedDelegate OnWeaponPulledFromTarget;

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Weapons")
    UStaticMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Weapons")
    UBoxComponent* WeaponCollisionBox;

    // 必须声明 UFUNCTION 宏，否则无法正确绑定
    UFUNCTION()
    void OnWeaponCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                          int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnWeaponCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                        int32 OtherBodyIndex);
};
