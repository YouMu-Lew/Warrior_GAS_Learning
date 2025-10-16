// YouMu All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Characters/WarriorBaseCharacter.h"

#include "WarriorHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class WARRIOR_GAS_LEARNING_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
    GENERATED_BODY()

public:
    AWarriorHeroCharacter();

protected:
    virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
#pragma region Components

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera",
              meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera",
              meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

#pragma endregion

#pragma region Inputs

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData",
              meta = (AllowPrivateAccess = "true"))
    UDataAsset_InputConfig* InputConfigDataAsset;

    void Input_Move(const FInputActionValue& InputActionValue);

#pragma endregion
};
