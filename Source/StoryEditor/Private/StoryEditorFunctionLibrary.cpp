#include "StoryEditorFunctionLibrary.h"
#include "StoryAsset.h"
#include <Widgets/Layout/SBorder.h>
#include <../Plugins/Editor/EditorScriptingUtilities/Source/EditorScriptingUtilities/Public/EditorAssetLibrary.h>
#include <Widgets/SWindow.h>
#include <Framework/Application/SlateApplication.h>
#include <UMGEditor/Public/WidgetBlueprint.h>
#include "FileHelpers.h"
#include "StoryEditorPickerBase.h"
#include "StoryEditorWidgetBase.h"

#define LOCTEXT_NAMESPACE "FStorySystemEditor"

void UStoryEditorFunctionLibrary::OnOpenEditor(UStoryAsset *asset)
{
	FString windowName = "Story Editor";
	if (asset)
	{
		windowName += " <";
		windowName += asset->GetName();
		windowName += ">";
	}

	TSharedRef<SWindow> EditorTab = SNew(SWindow)
										.AutoCenter(EAutoCenter::PreferredWorkArea)
										.Title(FText::FromString(windowName))
										.IsInitiallyMaximized(false)
										.ClientSize(FVector2D(1280, 720))
										.SizingRule(ESizingRule::UserSized)
										.SupportsMaximize(true)
										.SupportsMinimize(true)
										.CreateTitleBar(true)
										.HasCloseButton(true);

	//~ We need world
	UWorld *World = GEditor->GetEditorWorldContext().World();
	check(World);

	// UMG
	UWidgetBlueprint *umgAsset = Cast<UWidgetBlueprint>(UEditorAssetLibrary::LoadAsset(FString(TEXT("UserWidget'/StorySystem/StoryEditor/StoryEditorUI.StoryEditorUI'"))));
	UClass *WidgetClass = umgAsset->GeneratedClass;
	UStoryEditorWidgetBase *CreatedUMGWidget = CreateWidget<UStoryEditorWidgetBase>(World, WidgetClass);
	if (CreatedUMGWidget)
	{
		EditorTab->SetContent(CreatedUMGWidget->TakeWidget());

		FSlateApplication::Get().AddWindow(EditorTab);
		CreatedUMGWidget->UpdateStoryAsset(asset);

		FOpenedWindow windowData;
		windowData.WindowObj = &EditorTab.Get();
		CreatedUMGWidget->SetWindow(windowData);
		FocusWindow(windowData);
	}
}

UUserWidget *UStoryEditorFunctionLibrary::OpenPicker(TSubclassOf<UUserWidget> pickUMGClass)
{
	if (pickUMGClass)
	{
		TSharedRef<SWindow> EditorTab = SNew(SWindow)
											.AutoCenter(EAutoCenter::PreferredWorkArea)
											.Title(FText::FromString(TEXT("选择窗口")))
											.IsInitiallyMaximized(false)
											.ClientSize(FVector2D(800, 600))
											.SizingRule(ESizingRule::UserSized)
											.SupportsMaximize(true)
											.SupportsMinimize(true)
											.CreateTitleBar(true)
											.HasCloseButton(true);

		UWorld *World = GEditor->GetEditorWorldContext().World();
		check(World);

		// UMG
		UUserWidget *CreatedUMGWidget = CreateWidget<UUserWidget>(World, pickUMGClass);
		if (CreatedUMGWidget)
		{
			EditorTab->SetContent(CreatedUMGWidget->TakeWidget());
			FSlateApplication::Get().AddWindow(EditorTab);
			UStoryEditorPickerBase *pickerBase = dynamic_cast<UStoryEditorPickerBase *>(CreatedUMGWidget);
			if (pickerBase)
			{
				FOpenedWindow windowData;
				windowData.WindowObj = &EditorTab.Get();
				pickerBase->SetWindow(windowData);
				FocusWindow(windowData);
			}
		}

		return CreatedUMGWidget;
	}

	return nullptr;
}

UObject *UStoryEditorFunctionLibrary::CreateAsset(TSubclassOf<UObject> assetClass, const FString &assetName, const FString &savePath)
{
	// Get asset package
	FString saveFullPath = savePath + assetName;
	UPackage *package = CreatePackage(*saveFullPath);

	// Set package dirty
	if (package)
	{
		package->SetDirtyFlag(true);
		auto asset = NewObject<UObject>(package, assetClass, *assetName, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);

		// Save
		// UEditorLoadingAndSavingUtils::SavePackages({package}, true);
		return asset;
	}

	return nullptr;
}

FString UStoryEditorFunctionLibrary::OpenWindowsDirection(const FString &Path, const FString &Title)
{
	FString oldPath;
	IDesktopPlatform *DesktopPlatform = FDesktopPlatformModule::Get();
	DesktopPlatform->OpenDirectoryDialog(nullptr, Title, Path, oldPath);
	return oldPath;
}

bool UStoryEditorFunctionLibrary::IsAssetExist(UObject *target)
{
	if (target)
	{
		return target->GetPackage() != nullptr;
	}

	UE_LOG(LogTemp, Error, TEXT("Saving asset is null!"))
	return false;
}

bool UStoryEditorFunctionLibrary::MarkAssetDirty(UObject *asset)
{
	if (asset)
	{
		UPackage *package = asset->GetPackage();

		if (package)
		{
			package->SetDirtyFlag(true);
			return true;
		}
	}

	return false;
}

bool UStoryEditorFunctionLibrary::CloseWindow(const FOpenedWindow& windowData)
{
	if (windowData.WindowObj)
	{
		windowData.WindowObj->RequestDestroyWindow();
		return true;
	}

	return false;
}

bool UStoryEditorFunctionLibrary::FocusWindow(const FOpenedWindow& windowData) 
{
	if (windowData.WindowObj)
	{
		windowData.WindowObj->BringToFront(true);

		return true;
	}
		
	return false;
}

bool UStoryEditorFunctionLibrary::GetTargetAssets(TSubclassOf<UObject> assetClass, const FString &findPath, TArray<UObject *> &outAssets)
{
	TArray<FString> assetPaths = UEditorAssetLibrary::ListAssets(findPath);
	
	outAssets.Empty();
	for (int i = 0; i < assetPaths.Num(); ++i)
	{
		FAssetData _assetData = UEditorAssetLibrary::FindAssetData(assetPaths[i]);
		if (_assetData.AssetClass.ToString() == assetClass->GetName())
		{
			outAssets.Add(UEditorAssetLibrary::LoadAsset(assetPaths[i]));
		}
		
	}
	
	return outAssets.Num() > 0;
}
