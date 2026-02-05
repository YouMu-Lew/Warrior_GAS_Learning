// YouMu All Rights Reserved.

#include "Characters/WarriorEnemyCharacter.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_EnemyStartUpBase.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Widgets/WarriorWidgetBase.h"

#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

#include "WarriorDebugHelper.h"

AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
    // 设置 AI 自动控制：在场景放置或生成时由 AI 接管
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // 禁用从 Controller 继承俯仰（Pitch）旋转
    bUseControllerRotationPitch = false;
    // 禁用从 Controller 继承偏航（Yaw）旋转
    bUseControllerRotationYaw   = false;
    // 禁用从 Controller 继承横滚（Roll）旋转
    bUseControllerRotationRoll  = false;

    // 不使用 Controller 的期望旋转来驱动角色移动组件
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    // 启用角色朝向与移动方向对齐（移动时自动面向移动方向）
    GetCharacterMovement()->bOrientRotationToMovement     = true;
    // 设置角色旋转速率（仅影响朝向调整速度）
    GetCharacterMovement()->RotationRate                  = FRotator(0.f, 180.f, 0.f);
    // 设置角色的最大行走速度
    GetCharacterMovement()->MaxWalkSpeed                  = 300.f;
    // 设置行走时的减速刹车强度，用于停止时的减速速度
    GetCharacterMovement()->BrakingDecelerationWalking    = 1000.f;

    // 初始化默认值
    EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

    EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

    EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
    EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent() const
{
    return EnemyCombatComponent;
}

UPawnUIComponent* AWarriorEnemyCharacter::GetPawnUIComponent() const
{
    return EnemyUIComponent;
}

UEnemyUIComponent* AWarriorEnemyCharacter::GetEnemyUIComponent() const
{
    return EnemyUIComponent;
}

void AWarriorEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    UWarriorWidgetBase* HealthWidget = Cast<UWarriorWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject());
    if (HealthWidget)
    {
        HealthWidget->InitEnemyCreatedWidget(this);
    }
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    InitEnemyStartUpData();
}

void AWarriorEnemyCharacter::InitEnemyStartUpData()
{
    if (CharacterStartUpData.IsNull())
    {
        return;
    }

    UAssetManager::GetStreamableManager().RequestAsyncLoad(
        CharacterStartUpData.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([this]() {
            if (UDataAsset_StartUpBase* LoadedStartUpData = CharacterStartUpData.Get())
            {
                LoadedStartUpData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
            }
        }));
}
