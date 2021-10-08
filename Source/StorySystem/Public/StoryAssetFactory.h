#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "StoryAsset.h"
#include "AssetTypeCategories.h"

#include "StoryAssetFactory.generated.h"

UCLASS()
class STORYSYSTEM_API UStoryAssetFactory : public UFactory
{
    GENERATED_BODY()
public:
    UStoryAssetFactory()
    {
        bCreateNew = true;
        bEditAfterNew = true;
        SupportedClass = UStoryAsset::StaticClass();
    }

    virtual UObject *FactoryCreateNew(UClass *InClass, UObject *InParent, FName InName, EObjectFlags Flags, UObject *Context, FFeedbackContext *Warn, FName CallingContext)
    {
        return NewObject<UStoryAsset>(InParent, InName, Flags | RF_Transactional);
    }

    virtual uint32 GetMenuCategories() const override
    {
        return EAssetTypeCategories::Type::Gameplay;
    }
};
