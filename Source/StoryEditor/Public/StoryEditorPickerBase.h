#pragma once

#include <Blueprint/UserWidget.h>
#include "StoryAsset.h"
#include <IDesktopPlatform.h>
#include <DesktopPlatformModule.h>
#include "StoryEditorFunctionLibrary.h"
#include "StoryEditorPickerBase.generated.h"


UCLASS(BlueprintType, Blueprintable)
class STORYEDITOR_API UStoryEditorPickerBase : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="StoryEditor")
    FOpenedWindow CurrentWindow;


    void SetWindow(FOpenedWindow window)
    {
        CurrentWindow = window;
    }

};