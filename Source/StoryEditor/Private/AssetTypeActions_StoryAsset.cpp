#include "AssetTypeActions_StoryAsset.h"
#include "StoryAsset.h"
// #include "StoryEditor.h"
#include "StoryEditorFunctionLibrary.h"

#define LOCTEXT_NAMESPACE "StoreAsset"

FColor FAssetTypeActions_StoryAsset::GetTypeColor() const
{
    return FColor(255, 123, 123);
}

FText FAssetTypeActions_StoryAsset::GetName() const
{
    return LOCTEXT("StoreAssetTypeActions", "StoreAsset");
}

void FAssetTypeActions_StoryAsset::OpenAssetEditor(const TArray<UObject *> &InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
    //FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
	if (InObjects.Num() > 0)
	{
		UStoryAsset* asset = dynamic_cast<UStoryAsset*>(InObjects[0]);
		if (asset)
			UStoryEditorFunctionLibrary::OnOpenEditor(asset);
	}
}

UClass *FAssetTypeActions_StoryAsset::GetSupportedClass() const
{
    return UStoryAsset::StaticClass();
}

uint32 FAssetTypeActions_StoryAsset::GetCategories()
{
    return EAssetTypeCategories::Type::Gameplay;
}

bool FAssetTypeActions_StoryAsset::HasActions(const TArray<UObject*>& InObjects) const
{
    return true;
}

void FAssetTypeActions_StoryAsset::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	FAssetTypeActions_Base::GetActions(InObjects, MenuBuilder);

	auto assets = GetTypedObjectPtrs<UStoryAsset>(InObjects);

    MenuBuilder.AddMenuEntry(LOCTEXT("StoryEditor", "Open Story Editor"), 
        LOCTEXT("StorySystemToolTip", "Open Story Editor To Edit Story"),
        FSlateIcon(FSlateIcon()),
		FUIAction(
			FExecuteAction::CreateLambda([=] {
				// Open story editor
				if (InObjects.Num() > 0 && InObjects[0] != nullptr)
				{
					UStoryAsset* asset = dynamic_cast<UStoryAsset*>(InObjects[0]);
					if (asset)
					{
						UStoryEditorFunctionLibrary::OnOpenEditor(asset);
					}
				}
				}),
			FCanExecuteAction::CreateLambda([=] { // ѡ�е�Object������һ������nullptr����Ҫִ�д�������.
				for (auto asset : assets)
				{
					if (asset == nullptr)
					{
						return false;
					}
				}
				return true;
				}))
		);
}

#undef LOCTEXT_NAMESPACE
