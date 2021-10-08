/*
    Author: baihan 
    Date: "2021-08-26" 
    Class discription: Use to edit story 
*/

#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
#include "StoryPlayer.generated.h"

class UStoryAsset;

USTRUCT(BlueprintType)
struct FPlayerData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryPlayer)
    int UnitIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryPlayer)
    int FrameIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryPlayer)
    bool IsSkip = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryPlayer)
    bool IsAuto = false;
};

UCLASS(BlueprintType)
class STORYSYSTEM_API UStoryPlayer : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    bool UpdateData(UStoryAsset* storyAsset);

#pragma region Core Operation
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    bool Switch(int unitIndex, int frameIndex, bool isFirstFrame = false);
#pragma endregion

#pragma region operation
    UFUNCTION(BlueprintCallable)
    void Play(const FString& unitName = "");

    UFUNCTION(BlueprintCallable)
    bool PlayNext();

    UFUNCTION(BlueprintCallable)
    bool SwitchFrameByName(const FString& frameName);

    UFUNCTION(BlueprintCallable)
    bool SwitchUnitByName(const FString& unitName);

    UFUNCTION(BlueprintCallable)
    void UpdateSkip(bool bSkip);

    UFUNCTION(BlueprintCallable)
    void UpdateAuto(bool bAuto);
#pragma endregion

public:
    UPROPERTY(BlueprintReadWrite)
    UStoryAsset* Info;
    UPROPERTY(BlueprintReadWrite)
    FPlayerData Data;
};