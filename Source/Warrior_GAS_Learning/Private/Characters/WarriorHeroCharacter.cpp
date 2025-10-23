// YouMu All Rights Reserved.

#include "Characters/WarriorHeroCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/WarriorInputComponent.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/WarriorAttributeSet.h"

#include "WarriorDebugHelper.h"

/**
 * AWarriorHeroCharacter构造函数
 *
 * 初始化战士英雄角色的基本属性和组件设置，包括碰撞体大小、控制器旋转设置、
 * 摄像头摇臂组件、跟随摄像机以及角色移动相关参数
 */
AWarriorHeroCharacter::AWarriorHeroCharacter()
{
    // 设置角色胶囊体碰撞组件的尺寸大小
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    // 禁用控制器对角色旋转的控制，让角色能够独立于控制器进行旋转
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw   = false;
    bUseControllerRotationRoll  = false;

    // 创建并配置摄像头摇臂组件，用于实现第三人称视角的摄像机跟随效果
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetRootComponent());
    CameraBoom->TargetArmLength         = 200.f;                    // 设置摇臂长度
    CameraBoom->SocketOffset            = FVector(0.f, 55.f, 65.f); // 设置摄像机相对偏移
    CameraBoom->bUsePawnControlRotation = true;                     // 允许摇臂跟随角色控制器旋转

    // 创建并配置跟随摄像机组件，附加到摄像头摇臂上
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false; // 禁用摄像机自身的控制器旋转

    // 配置角色移动组件的各项参数，实现流畅的第三人称移动控制
    GetCharacterMovement()->bOrientRotationToMovement  = true; // 角色朝向与移动方向一致
    GetCharacterMovement()->RotationRate               = FRotator(0.f, 500.f, 0.f); // 设置旋转速率
    GetCharacterMovement()->MaxWalkSpeed               = 400.f;  // 设置最大行走速度
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 设置行走时刹车减速度
}

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (WarriorAbilitySystemComponent && WarriorAttributeSet) {
        const FString ASCText =
            FString::Printf(TEXT("Owner Actor: %s, AvatarActor: %s"),
                            *WarriorAbilitySystemComponent->GetOwnerActor()->GetActorLabel(),
                            *WarriorAbilitySystemComponent->GetAvatarActor()->GetActorLabel());

        Debug::Print(TEXT("Ability system component valid.") + ASCText);
        Debug::Print(TEXT("Attribute set valid."));
    }
}

void AWarriorHeroCharacter::BeginPlay()
{
    Super::BeginPlay();

    Debug::Print(TEXT("Working..."));
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config."))

        ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

    auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

    check(Subsystem);

    Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

    auto* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);

    WarriorInputComponent->BindNativeInputAction(
        InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this,
        &ThisClass::Input_Move);
    WarriorInputComponent->BindNativeInputAction(
        InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this,
        &ThisClass::Input_Look);
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
    const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

    const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

    if (MovementVector.Y != 0.f) {
        const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

        AddMovementInput(ForwardDirection, MovementVector.Y);
    }

    if (MovementVector.X != 0.f) {
        const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
    const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

    if (LookAxisVector.X != 0.f) {
        AddControllerYawInput(LookAxisVector.X);
    }

    if (LookAxisVector.Y != 0.f) {
        AddControllerPitchInput(LookAxisVector.Y);
    }
}
