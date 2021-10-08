#pragma once

#include <Blueprint/UserWidget.h>
#include "StoryAsset.h"
#include <IDesktopPlatform.h>
#include <DesktopPlatformModule.h>
#include "StoryEditorFunctionLibrary.h"
#include "StoryEditorWidgetBase.generated.h"


UCLASS(BlueprintType, Blueprintable)
class STORYEDITOR_API UStoryEditorWidgetBase : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="StoryEditor")
    UStoryAsset* TargetAsset;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="StoryEditor")
    FOpenedWindow CurrentWindow;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void UpdateStoryAsset(UStoryAsset* target);
    virtual void UpdateStoryAsset_Implementation(UStoryAsset* target)
    {
        TargetAsset = target;
    }

    UFUNCTION(BlueprintCallable)
    bool HasPackage()
    {
        if (TargetAsset->GetPackage())
            return true;
        return false;
    }

    void SetWindow(FOpenedWindow window)
    {
        CurrentWindow = window;
    }

};