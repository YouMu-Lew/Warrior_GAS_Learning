#pragma once

namespace Debug {

    static void Print(const FString& Msg, const FColor& Color = FColor::MakeRandomColor(),
                      int32 InKey = -1, float TimeToDisplay = 5.0f)
    {
        if (GEngine) {
            GEngine->AddOnScreenDebugMessage(InKey, TimeToDisplay, Color, Msg);

            UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
        }
    }

} // namespace Debug