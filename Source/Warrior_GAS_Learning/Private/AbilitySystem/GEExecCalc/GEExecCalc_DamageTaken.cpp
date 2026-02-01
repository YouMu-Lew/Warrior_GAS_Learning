// YouMu All Rights Reserved.

#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/WarriorAttributeSet.h"
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

struct FWarriorDamageCapture
{
    // 声明需要捕获的属性
    DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

    FWarriorDamageCapture()
    {
        // 定义需要捕获的属性，Source 和 Target 分别表示 来源 和 目标 的属性
        DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackPower, Source, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefensePower, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DamageTaken, Target, false);
    }
};

static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
    static FWarriorDamageCapture DamageCapture;
    return DamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
    // Slow way of doing capture
    // FProperty* AttackPowerProperty =
    //    FindFieldChecked<FProperty>(UWarriorAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet, AttackPower));

    // FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(AttackPowerProperty,
    //                                                                        EGameplayEffectAttributeCaptureSource::Source, false);

    // RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

    // Fast way of doing capture
    RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
    RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef);
    RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                     FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Black, TEXT("--------------------------------"));

    const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

    FAggregatorEvaluateParameters EvaluateParameters;
    EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
    EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

    float SourceAttackPower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef, EvaluateParameters,
                                                               SourceAttackPower);
    // Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

    float TargetDefensePower = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef, EvaluateParameters,
                                                               TargetDefensePower);
    // Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

    EffectSpec.SetByCallerTagMagnitudes;

    float BaseDamage                = 0.f;
    int32 UsedLightAttackComboCount = 0;
    int32 UsedHeavyAttackComboCount = 0;

    for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes) {
        if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage)) {
            BaseDamage = TagMagnitude.Value;

            // Debug::Print(TEXT("BaseDamage_1"), BaseDamage);
        } else if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_LightAttack)) {
            UsedLightAttackComboCount = FMath::TruncToInt(TagMagnitude.Value);
            // Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
        } else if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_HeavyAttack)) {
            UsedHeavyAttackComboCount = FMath::TruncToInt(TagMagnitude.Value);
            // Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
        }
    }

    // 实际的伤害计算公式
    /* 每层轻攻击 (连击数 - 1) 增加的基础伤害百分比 */
    const float LightAttackComboDamagePercentPerStack = 0.05f;
    /* 每层重攻击连击数增加的基础伤害百分比 */
    const float HeavyAttackComboDamagePercentPerStack = 0.15f;

    if (UsedLightAttackComboCount > 1) {
        BaseDamage *= (1.f + LightAttackComboDamagePercentPerStack * (UsedLightAttackComboCount - 1));
        // Debug::Print(TEXT("BaseDamage_2"), BaseDamage);
    }

    if (UsedHeavyAttackComboCount > 1) {
        BaseDamage *= (1.f + HeavyAttackComboDamagePercentPerStack * UsedHeavyAttackComboCount);
        // Debug::Print(TEXT("BaseDamage_3"), BaseDamage);
    }

    // 最终伤害计算公式
    const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;
    //Debug::Print(TEXT("FinalDamage"), FinalDamage);

    if (FinalDamage > 0.f) {
        OutExecutionOutput.AddOutputModifier(
            FGameplayModifierEvaluatedData(GetWarriorDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamage));
    }

    GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Black, TEXT("--------------------------------"));
}
