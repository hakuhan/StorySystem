// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowStoryActor.h"
#include "StoryPlayer.h"
#include "StorySystemFunctionLibrary.h"

// Sets default values
AShowStoryActor::AShowStoryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AShowStoryActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (m_StoryPlayerClass && m_StoryAsset)
	{
		auto storyWidget = UStorySystemFunctionLibrary::OpenStory(this, m_StoryPlayerClass, m_StoryAsset);
		if (storyWidget)
		{
			storyWidget->AddToViewport();
			storyWidget->Play();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot create widget!"))
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Please setup story class and asset"))
	}
}
