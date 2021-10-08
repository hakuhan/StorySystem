// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryEditor.h"
#include "StoryEditorStyle.h"
#include "StoryEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "AssetTypeActions_StoryAsset.h"
#include "StoryEditorFunctionLibrary.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FStoryEditorModule"

void FStoryEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FStoryEditorStyle::Initialize();
	FStoryEditorStyle::ReloadTextures();

	FStoryEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStoryEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStoryEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStoryEditorModule::RegisterMenus));

	// Regist story asset
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_StoryAsset()));
}

void FStoryEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStoryEditorStyle::Shutdown();

	FStoryEditorCommands::Unregister();
}

void FStoryEditorModule::PluginButtonClicked()
{
	UStoryEditorFunctionLibrary::OnOpenEditor();
}

void FStoryEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStoryEditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStoryEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FStoryEditorModule, StoryEditor)