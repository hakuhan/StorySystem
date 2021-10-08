#pragma once

#include "CoreMinimal.h"
#include "Widgets/Docking/SDockTab.h"
#include "Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h"
#include "StoryEditorFunctionLibrary.generated.h"

class UStoryAsset;
class SWindow;

USTRUCT(BlueprintType)
struct FOpenedWindow
{
	GENERATED_USTRUCT_BODY()

	SWindow* WindowObj;
};

UCLASS()
class STORYEDITOR_API UStoryEditorFunctionLibrary :
    public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void OnOpenEditor(UStoryAsset* asset = nullptr);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "pickUMGClass"))
	static UUserWidget* OpenPicker(TSubclassOf<UUserWidget> pickUMGClass);

	UFUNCTION(BlueprintCallable)
	static UObject* CreateAsset(TSubclassOf<UObject> assetClass, const FString& assetName = "NewAsset", const FString& savePath = TEXT("/Game/"));

	UFUNCTION(BlueprintCallable)
	static FString OpenWindowsDirection(const FString& Path = "/Game/", const FString& Title = TEXT("选择保存路径"));

	UFUNCTION(BlueprintCallable)
	static bool IsAssetExist(UObject* asset);

	UFUNCTION(BlueprintCallable)
	static bool MarkAssetDirty(UObject* asset);

	UFUNCTION(BlueprintCallable)
	static bool CloseWindow(const FOpenedWindow& windowData);

	UFUNCTION(BlueprintCallable)
	static bool FocusWindow(const FOpenedWindow& windowData);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "assetClass"))
	static bool GetTargetAssets(TSubclassOf<UObject> assetClass, const FString& findPath, TArray<UObject*>& outAssets);
};