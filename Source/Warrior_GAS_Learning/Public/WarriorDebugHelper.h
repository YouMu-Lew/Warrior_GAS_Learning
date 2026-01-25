#pragma once

namespace Debug {

    static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1, float TimeToDisplay = 5.0f)
    {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(InKey, TimeToDisplay, Color, Msg);

            UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
        }
    }

    static void Print(const FString& FloatTitle, float FloatValue, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1,
                      float TimeToDisplay = 7.0f)
    {
        if (GEngine) {
            const FString FinalMsg = FString::Printf(TEXT("%s: %f"), *FloatTitle, FloatValue);
            GEngine->AddOnScreenDebugMessage(InKey, TimeToDisplay, Color, FinalMsg);

            UE_LOG(LogTemp, Warning, TEXT("%s"), *FinalMsg);
        }
    }

} // namespace Debug