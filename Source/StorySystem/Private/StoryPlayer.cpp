#include "StoryPlayer.h"
#include "StoryAsset.h"

bool UStoryPlayer::UpdateData(UStoryAsset *storyAsset)
{
    if (storyAsset)
    {
        Info = storyAsset;
        return true;
    }

    UE_LOG(LogTemp, Error, TEXT("Story asset is invalid!"))
    return false;
}

void UStoryPlayer::Play(const FString &unitName)
{
    if (Info == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Story asset is invalid!"))
        return;
    }

    int unitIndex = 0;

    // Set unit index
    if (!unitName.IsEmpty())
    {
        int _unitIndex = Info->Units.IndexOfByPredicate([&](const FStoryUnit &_unit)
        { 
            return _unit.Name == unitName; 
        });
        if (_unitIndex >= 0)
        {
            unitIndex = _unitIndex;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Cannot find target unit:%s"), *unitName)
        }
    }

    Switch(unitIndex, 0, true);
}

bool UStoryPlayer::PlayNext()
{
    if (Info == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Story asset is invalid!"))
        return false;
    }

    // Get next unit and frame
    int unitIndex = -1;
    int frameIndex = -1;
    if (Info->Units.Num() > Data.UnitIndex)
    {
        if (Data.FrameIndex + 1 < Info->Units[Data.UnitIndex].Frames.Num())
        {
            unitIndex = Data.UnitIndex;
            frameIndex = Data.FrameIndex + 1;
        }
        else if (Data.UnitIndex + 1 < Info->Units.Num())
        {
            unitIndex = Data.UnitIndex + 1;
            frameIndex = 0;
        }
    }

    // Switch
    if (unitIndex >= 0 && frameIndex >= 0)
    {
        return Switch(unitIndex, frameIndex);
    }

    return false;
}

bool UStoryPlayer::SwitchFrameByName(const FString &frameName)
{
    if (Info == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Story asset is invalid!"))
        return false;
    }

    if (Info->Units.Num() >= Data.UnitIndex)
    {
        int _frameIndex = Info->Units[Data.UnitIndex].Frames.IndexOfByPredicate([&](const FStoryFrame &_frame)
        { 
            return _frame.Name == frameName; 
        });

        if (_frameIndex >= 0)
        {
            return Switch(Data.UnitIndex, _frameIndex);
        }
        else
        {
            return false;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Story unit is out of range"))
        return false;
    }
}

bool UStoryPlayer::SwitchUnitByName(const FString& unitName) {
    if (Info == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Story asset is invalid!"))
        return false;
    }

    int unitIndex = -1;

    // Set unit index
    if (!unitName.IsEmpty())
    {
        unitIndex = Info->Units.IndexOfByPredicate([&](const FStoryUnit &_unit)
        { 
            return _unit.Name == unitName; 
        });
    }

    if (unitIndex >= 0)
    {
        return Switch(unitIndex, 0);
    }
    else
    {
        return false;
        UE_LOG(LogTemp, Warning, TEXT("Cannot find target unit:%s"), *unitName)
    }
}

void UStoryPlayer::UpdateSkip(bool bSkip)
{
    if (Info == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Story asset is invalid!"))
        return;
    }
}

void UStoryPlayer::UpdateAuto(bool bAuto)
{
    if (Info == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Story asset is invalid!"))
        return;
    }
}
