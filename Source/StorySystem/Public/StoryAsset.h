#pragma once

#include "CoreMinimal.h"
#include "StoryAsset.generated.h"

class USoundCue;
struct FSlateBrush;

USTRUCT(BlueprintType)
struct FStoryFrameImageInfo
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    FSlateBrush Image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    bool UseLastFrame = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    int ShowingIndex = -1;
};

USTRUCT(BlueprintType)
struct STORYSYSTEM_API FStoryFrame : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    FString Text;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    FSlateBrush Background;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    TArray<FStoryFrameImageInfo> Images;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    USoundCue* Voice;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StoryResource)
    USoundCue* BGM;
};

USTRUCT(BlueprintType)
struct STORYSYSTEM_API FStoryUnit : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Name;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FStoryFrame> Frames;
};


UCLASS(BlueprintType)
class STORYSYSTEM_API UStoryAsset : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Story)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Story)
    TArray<FStoryUnit> Units;
};