// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WarriorWidgetBase.generated.h"

class UHeroUIComponent;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API UWarriorWidgetBase : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void InitEnemyCreatedWidget(AActor* OwningEnemyActor);

protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
    void BP_OnOwningHeroUIComponentInitialized(UHeroUIComponent* OwningHeroUIComponent);

    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
    void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);
};
