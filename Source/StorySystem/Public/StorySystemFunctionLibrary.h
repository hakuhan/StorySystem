#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h"

#include "StorySystemFunctionLibrary.generated.h"

class UStoryPlayer;
class UStoryAsset;

UCLASS()
class STORYSYSTEM_API UStorySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "playerClass"))
	static UStoryPlayer* OpenStory(const UObject* WorldContextObject, TSubclassOf<UStoryPlayer> playerClass, UStoryAsset* storyAsset);
};