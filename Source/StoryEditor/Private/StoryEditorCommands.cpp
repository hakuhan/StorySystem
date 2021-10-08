// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoryEditorCommands.h"

#define LOCTEXT_NAMESPACE "FStoryEditorModule"

void FStoryEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "StoryEditor", "Bring up StoryEditor window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
