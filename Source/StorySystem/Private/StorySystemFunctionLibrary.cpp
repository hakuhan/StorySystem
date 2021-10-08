#include "StorySystemFunctionLibrary.h"
#include "StoryAsset.h"
#include "StoryPlayer.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UStoryPlayer* UStorySystemFunctionLibrary::OpenStory(const UObject* WorldContextObject, TSubclassOf<UStoryPlayer> playerClass, UStoryAsset* storyAsset) 
{
	UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	check(World);

	UStoryPlayer* storyPlayer = nullptr;
	// Find player in scene
	TArray<UUserWidget*> widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(World, widgets, playerClass);
	if (widgets.Num() > 0)
	{
		storyPlayer = dynamic_cast<UStoryPlayer*>(widgets[0]);
	}
	
	// Create a new player
	if (storyPlayer == nullptr)
	{
		auto playerCtr = GEditor->GetFirstLocalPlayerController(World);
		if (playerCtr)
		{
			storyPlayer = CreateWidget<UStoryPlayer>(playerCtr, playerClass);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot get player!"))	
		}
	}
	
	// Init player data
	if (storyPlayer)
	{
		storyPlayer->UpdateData(storyAsset);
	}
	
	return storyPlayer;
}