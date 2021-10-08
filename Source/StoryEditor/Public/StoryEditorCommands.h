// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "StoryEditorStyle.h"

class FStoryEditorCommands : public TCommands<FStoryEditorCommands>
{
public:

	FStoryEditorCommands()
		: TCommands<FStoryEditorCommands>(TEXT("StoryEditor"), NSLOCTEXT("Contexts", "StoryEditor", "StoryEditor Plugin"), NAME_None, FStoryEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};