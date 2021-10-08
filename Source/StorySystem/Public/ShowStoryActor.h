// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShowStoryActor.generated.h"

class UStoryAsset;
class UStoryPlayer;

UCLASS()
class STORYSYSTEM_API AShowStoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShowStoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Story")
	TSubclassOf<UStoryPlayer> m_StoryPlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Story")
	UStoryAsset* m_StoryAsset;
};
